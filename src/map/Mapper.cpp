#include <iostream>

#include "Mapper.h"
#include "MapVisualizer.h"
#include "FileUtils.h"
#include "ArrayUtils.h"

using namespace std;

shared_ptr<Mapper> Mapper::mapper = nullptr;

Mapper::Mapper() :
		mapVisualizer(nullptr),
		mapViewOpen(false), checkpointsAdded(false) {
}

shared_ptr<Mapper> Mapper::getInstance() {

	if (mapper == nullptr) {
		mapper = make_shared<Mapper>();
		;
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
}



