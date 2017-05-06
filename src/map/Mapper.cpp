#include <iostream>
#include "Mapper.h"
#include "MapVisualizer.h"

using namespace std;

shared_ptr<Mapper> Mapper::mapper = nullptr;

Mapper::Mapper() :
		mapViewOpen(false) {
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
		std::cout << "Mapview is: " << mapViewOpen << "\n";
		return;
	}

	mapViewOpen = true;
	MapVisualizer *mapWindow = new MapVisualizer(
			[&]() -> void {this->mapViewOpen = false;});
	mapWindow->show();

}



