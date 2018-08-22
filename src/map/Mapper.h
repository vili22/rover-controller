#ifndef MAP_MAPPER_H_
#define MAP_MAPPER_H_

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include <QMetaType>
#include <QObject>

class MapVisualizer;

class Mapper: public QObject {
Q_OBJECT

public:
	Mapper();
	void viewMap();
	static std::shared_ptr<Mapper> getInstance();
	bool readCheckPoints(std::string filename);
	void closeMapView();
	void addPathPoint(float t, float x, float y, float z);
signals:
	void newPathPoint(glm::vec3 point);

private:
	static std::shared_ptr<Mapper> mapper;
	MapVisualizer *mapVisualizer;
	std::vector<std::vector<float>> checkpoints;
	std::vector<glm::vec4> pathPoints;
	std::vector<glm::vec3> visualizedPoints;
	bool mapViewOpen, checkpointsAdded;
};



#endif /* MAP_MAPPER_H_ */
