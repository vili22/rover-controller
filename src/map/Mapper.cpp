#include <iostream>

#include "Mapper.h"
#include "MapVisualizer.h"
#include "FileUtils.h"
#include "ArrayUtils.h"
#include "GeometryUtils.h"

using namespace std;

shared_ptr<Mapper> Mapper::mapper = nullptr;

Mapper::Mapper() :
		mapVisualizer(nullptr),
		mapViewOpen(false), checkpointsAdded(false) {

}

shared_ptr<Mapper> Mapper::getInstance() {

	if (mapper == nullptr) {
		mapper = make_shared<Mapper>();
	}

	return mapper;
}

void Mapper::viewMap() {

	if (mapViewOpen) {
		return;
	}

	mapViewOpen = true;
	mapVisualizer =
			new MapVisualizer(
					[&]() -> void {mapViewOpen = false; mapVisualizer = nullptr; checkpointsAdded = false;});
	mapVisualizer->show();

//	connect(this, SIGNAL(newPathPoint(glm::vec3)), mapVisualizer,
//			SLOT(addVisualizedPoint(glm::vec3 point)));
	connect(this, &Mapper::newPathPoint, mapVisualizer,
			&MapVisualizer::addVisualizedPoint);

	if (visualizedPoints.size() > 0) {
		mapVisualizer->setPathPoints(visualizedPoints);
	}

	if (checkpoints.size() > 0) {
		mapVisualizer->setCheckpoints(checkpoints);
		checkpointsAdded = true;
	}

}

bool Mapper::readCheckPoints(string filename) {

	checkpoints = utils::read_float_type_array<float>(filename);
	if (checkpoints.size() > 0) {
		if (mapVisualizer != nullptr && !checkpointsAdded) {
			mapVisualizer->setCheckpoints(checkpoints);
			checkpointsAdded = true;
		}
		return true;
	}

	return false;
}

void Mapper::closeMapView() {
	mapVisualizer->close();
	mapVisualizer = nullptr;
	checkpointsAdded = false;
	disconnect(this, SIGNAL(newPathPoint(glm::vec3)), 0, 0);
}

void Mapper::addPathPoint(float t, float x, float y, float z) {

	vector<float> p1 = { x, y, z };
	vector<float> p2;
	if (pathPoints.size() == 0) {
		p2 = {0.0f, 0.0f, 0.0f};
	} else {
		glm::vec3 tempPoint = visualizedPoints.at(visualizedPoints.size() -1);
		p2 = {tempPoint[0], tempPoint[1], tempPoint[2]};
	}

	if (pathPoints.size() == 0
			|| geometryutils::pointDistance<float>(p1, p2) > 0.25) {
		glm::vec3 prevVisualizedPoint(x, y, z);
		visualizedPoints.push_back(prevVisualizedPoint);
		if (mapViewOpen) {
			emit newPathPoint(prevVisualizedPoint);
			//mapVisualizer->addVisualizedPoint(prevVisualizedPoint);
		}
	}

	pathPoints.push_back(glm::vec4(t, x, y, z));
}



