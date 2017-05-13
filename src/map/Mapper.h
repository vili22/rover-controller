#ifndef MAP_MAPPER_H_
#define MAP_MAPPER_H_

#include <memory>
#include <string>
#include <vector>

#include "MapVisualizer.h"

class Mapper {

public:
	Mapper();
	void viewMap();
	static std::shared_ptr<Mapper> getInstance();
	bool readCheckPoints(std::string filename);
	void closeMapView();

private:
	static std::shared_ptr<Mapper> mapper;
	MapVisualizer *mapVisualizer;
	std::vector<std::vector<float>> checkpoints;
	bool mapViewOpen, checkpointsAdded;
};



#endif /* MAP_MAPPER_H_ */
