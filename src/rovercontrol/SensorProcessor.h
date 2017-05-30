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
#include <memory>

#include <Eigen/Dense>

#include "Quaternions.h"
#include "WheelEncoder.h"

class SensorProcessor {


	public:

		SensorProcessor();
        ~SensorProcessor();
		void newSensorReading(std::string sensorReading);
		void newSensorReading(std::vector<double> sensorReading);
		void openSensorFile();
		void closeSensorFile();
		void setWriteToFile(bool writeToFile);
		std::vector<double> getState();
		static std::shared_ptr<SensorProcessor> getInstance();
		std::vector<int> getTicks();

	private:

	    static std::shared_ptr<SensorProcessor> sensorProcessor;
		void accUpdate(std::vector<std::string> input);
		void gyroUpdate(std::vector<std::string> input);

		Eigen::Quaterniond deviceOrientation;
		bool systemInitalized, writeToFile;
		double prevTimeStamp;
		std::ofstream sensorFile;
		WheelEncoder wheelEncoder;

};


#endif /* SENSORPROCESSOR_H_ */
