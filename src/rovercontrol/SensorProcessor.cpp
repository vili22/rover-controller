/*
 * SensorProcessor.cpp
 *
 *  Created on: Jun 19, 2016
 *      Author: vvirkkal
 */
#include <iostream>
#include "StringUtils.h"

#include "SensorProcessor.h"

SensorProcessor::SensorProcessor() : systemInitalized(false) {

    writeToFile = false;
};

void SensorProcessor::closeSensorFile() {

	if(sensorFile.is_open()) {
		sensorFile.close();
	}
}

void SensorProcessor::newSensorReading(std::string sensorReading) {

	if(sensorFile.is_open()) {
		sensorFile << sensorReading << "\n";
	}

//	std::vector<std::string> input = utils::strSplit(sensorReading);
//
//	int sensor = std::stoi(input.at(0));
//
//	switch (sensor) {
//
//	case 0 :
//		accUpdate(input);
//		break;
//	case 1 :
//		gyroUpdate(input);
//		break;
//	default :
//		std::cout << "Unsupported sensor type\n";
//	}
}

void SensorProcessor::newSensorReading(std::vector<double> reading) {

    if(reading.size() <= 0) {
        return;
    }

    int type = (int)reading[0];

    switch(type) {
    case 0 :
        if(wheelEncoder.checkInputValidity(reading)) {
            this->wheelEncoder.update(reading);
        }
    }


}

void SensorProcessor::accUpdate(std::vector<std::string> input) {

	if(!this->systemInitalized) {
		double gravity[] = {0.0, 0.0, 1.0};
		double acc[] = {std::stod(input.at(2)), std::stod(input.at(3)), std::stod(input.at(4))};
		this->deviceOrientation = Quaternions::initFromVectors(Eigen::Vector3d(gravity), Eigen::Vector3d(acc));
		this->prevTimeStamp = std::stod(input.at(1));
	}
}

void SensorProcessor::gyroUpdate(std::vector<std::string> input) {

	if(~this->systemInitalized) {
		return;
	}

	double t = std::stod(input.at(1));
	double dt = t - this->prevTimeStamp;
	this->prevTimeStamp = t;
	double gyro[] = {std::stod(input.at(2)), std::stod(input.at(3)), std::stod(input.at(4))};
	this->deviceOrientation = Quaternions::gyroUpdate(this->deviceOrientation, gyro, dt);

}


