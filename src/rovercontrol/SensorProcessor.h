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
#include <Eigen/Dense>

#include "Quaternions.h"

class SensorProcessor {

	public:

		SensorProcessor();
		void newSensorReading(std::string sensorReading);

	private:
		void accUpdate(std::vector<std::string> input);
		void gyroUpdate(std::vector<std::string> input);

		Eigen::Quaterniond deviceOrientation;
		bool systemInitalized;
		double prevTimeStamp;

};


#endif /* SENSORPROCESSOR_H_ */
