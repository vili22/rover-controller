#ifndef MAP_MAPPER_H_
#define MAP_MAPPER_H_

#include <memory>

class Mapper {

public:
	Mapper();
	void viewMap();
	static std::shared_ptr<Mapper> getInstance();

private:
	static std::shared_ptr<Mapper> mapper;
	bool mapViewOpen;
};



#endif /* MAP_MAPPER_H_ */
