#include <fstream>
#include <sstream>
#include "FileUtils.h"

std::vector<std::vector<double>> utils::parse_sensor_data(std::string filename) {

    std::ifstream input;
	std::string line;
	std::vector<std::vector<double>> doubleArray;
	input.open(filename.c_str());
	if(!input.is_open()) {
        return doubleArray;
	}

	while(std::getline(input, line)) {
		std::istringstream numberStream(line);
		std::vector<double> lineValues;
		double value;
		while(numberStream >> value) {
			lineValues.push_back(value);
		}
		doubleArray.push_back(lineValues);
	}
    return doubleArray;
}
