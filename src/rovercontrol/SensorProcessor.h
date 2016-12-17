/*
 * SensorProcessor.h
 *
 *  Created on: Jun 19, 2016
 *      Author: vvirkkal
 */

#ifndef SENSORPROCESSOR_H_
#define SENSORPROCESSOR_H_

#include <string>
#include <vector>
#include <fstream>
#include <Eigen/Dense>

#include "Quaternions.h"
#include "WheelEncoder.h"

class SensorProcessor {

	public:

		SensorProcessor();
		void newSensorReading(std::string sensorReading);
		void newSensorReading(std::vector<double> sensorReading);
		void closeSensorFile();
		std::vector<double> getState();

	private:
		void accUpdate(std::vector<std::string> input);
		void gyroUpdate(std::vector<std::string> input);

		Eigen::Quaterniond deviceOrientation;
		bool systemInitalized, writeToFile;
		double prevTimeStamp;
		std::ofstream sensorFile;
		WheelEncoder wheelEncoder;

};


#endif /* SENSORPROCESSOR_H_ */
