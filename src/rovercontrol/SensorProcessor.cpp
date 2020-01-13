/*
 * SensorProcessor.cpp
 *
 *  Created on: Jun 19, 2016
 *      Author: vvirkkal
 */
#include <iostream>

#include "SensorProcessor.h"
#include "Configuration.h"
#include "Mapper.h"
#include "StringUtils.h"

using namespace std;
using namespace configuration;

shared_ptr<SensorProcessor> SensorProcessor::sensorProcessor = nullptr;

SensorProcessor::SensorProcessor() : systemInitalized(false),
                                     writeToFile(Configuration::getInstance()->getConfigurationBoolean("STORE_TO_FILE")) {

};

SensorProcessor::~SensorProcessor() {
    closeSensorFile();
}

shared_ptr<SensorProcessor> SensorProcessor::getInstance() {

    if(sensorProcessor == nullptr) {

        sensorProcessor = make_shared<SensorProcessor>();
    }

    return sensorProcessor;
}

void SensorProcessor::openSensorFile() {

    string path = "../../sensor-data/";
    string fileName = Configuration::getInstance()->getConfigurationString("FILE_STORAGE_NAME");
    sensorFile.open(path + fileName);

}

void SensorProcessor::closeSensorFile() {

	if(sensorFile.is_open()) {
		sensorFile.close();
	}
}

void SensorProcessor::newSensorReading(string sensorReading) {

	if(writeToFile && sensorFile.is_open()) {
		sensorFile << sensorReading << "\n";
		std::cout << sensorReading << "\n";
		return;
	}

	vector<double> reading = utils::convert_to_float_type<double>(
			utils::strSplit(sensorReading));
	newSensorReading(reading);
	std::vector<double> state = getState();
	Mapper::getInstance()->addPathPoint((float) state[0], (float) state[1],
			(float) state[2], 0.0f);

}

void SensorProcessor::newSensorReading(vector<double> reading) {

    if(reading.size() <= 0) {
        return;
    }

    int type = (int)reading[0];

    switch(type) {
    case 0 :
        if(wheelEncoder.checkInputValidity(reading)) {
			wheelEncoder.update(reading);
        }
    }
}

vector<double> SensorProcessor::getState() {
	return wheelEncoder.getRoverPositionState();
}

vector<int> SensorProcessor::getTicks() {
	return wheelEncoder.getTotalTicks();
}


void SensorProcessor::accUpdate(vector<string> input) {

	if(!this->systemInitalized) {
		double gravity[] = {0.0, 0.0, 1.0};
		double acc[] = {std::stod(input.at(2)), std::stod(input.at(3)), std::stod(input.at(4))};
		this->deviceOrientation = Quaternions::initFromVectors(Eigen::Vector3d(gravity), Eigen::Vector3d(acc));
		this->prevTimeStamp = std::stod(input.at(1));
	}
}

void SensorProcessor::gyroUpdate(std::vector<std::string> input) {

	if(!this->systemInitalized) {
		return;
	}

	double t = std::stod(input.at(1));
	double dt = t - this->prevTimeStamp;
	this->prevTimeStamp = t;
	double gyro[] = {std::stod(input.at(2)), std::stod(input.at(3)), std::stod(input.at(4))};
	this->deviceOrientation = Quaternions::gyroUpdate(this->deviceOrientation, gyro, dt);

}

void SensorProcessor::setWriteToFile(bool writeToFileFlag) {

    writeToFile = writeToFileFlag;
    if(writeToFile) {

        closeSensorFile();
        openSensorFile();
    }
}


