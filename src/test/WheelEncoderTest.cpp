/*
 * WheelEncoderTest.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: vvirkkal
 */

#include <iomanip>
#include <algorithm>

#include "gtest/gtest.h"

#include "FileUtils.h"
#include "SensorProcessor.h"


TEST(WheelEncoderTest, wheelEncoder) {

	std::string filename = "/home/vvirkkal/Documents/development/rover-controller/sensor-data/data.txt";
	std::vector<std::vector<double>> doubleArray = utils::parse_sensor_data(filename);
	std::sort(doubleArray.begin(), doubleArray.end(), [](const std::vector<double> &a,
                                                       const std::vector<double> &b){ return a[1] < b[1];});

	testing::internal::CaptureStdout();
    SensorProcessor sensorProcessor;

	std::cout << std::fixed;
	std::cout << std::setprecision(6);
    for(std::vector<std::vector<double>>::iterator it = doubleArray.begin(); it < doubleArray.end(); it++) {
        sensorProcessor.newSensorReading(*it);
        std::vector<double> state = sensorProcessor.getState();
        for(size_t ind = 0; ind < state.size(); ind++) {
            std::cout << state[ind] << " ";
        }
        std::cout << "\n";
	}

    std::string output = testing::internal::GetCapturedStdout();
	ASSERT_STREQ(output.c_str(), std::string("").c_str()) << output << "\n";
}




