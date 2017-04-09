/*
 * WheelEncoderTest.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: vvirkkal
 */

#include <iomanip>
#include <algorithm>
#include <cmath>

#include "gtest/gtest.h"

#include "FileUtils.h"
#include "SensorProcessor.h"
#include "Configuration.h"

using namespace std;
using namespace configuration;

TEST(WheelEncoderTest, wheelEncoder) {


    Configuration::initializeConfiguration();
	std::string filename = "/home/vvirkkal/Documents/development/rover-controller/sensor-data/data_suora1.txt";
	std::vector<std::vector<double>> doubleArray = utils::parse_sensor_data(filename);
	std::sort(doubleArray.begin(), doubleArray.end(), [](const std::vector<double> &a,
                                                       const std::vector<double> &b){ return a[1] < b[1];});

	testing::internal::CaptureStdout();
    for(std::vector<std::vector<double>>::iterator it = doubleArray.begin(); it < doubleArray.end(); it++) {
        SensorProcessor::getInstance()->newSensorReading(*it);
        std::vector<double> state = SensorProcessor::getInstance()->getState();
        for(size_t ind = 0; ind < state.size(); ind++) {
            if(ind == 2) {
                std::cout << state[ind] * 180/M_PI << " ";
            } else {
                std::cout << state[ind] << " ";
            }
        }
        std::cout << "\n";
	}
	vector<int> ticks = SensorProcessor::getInstance()->getTicks();
	std::cout<<"total left ticks: " << ticks[0] << " total right ticks: " << ticks[1] << "\n";

    std::string output = testing::internal::GetCapturedStdout();
	ASSERT_STREQ(output.c_str(), std::string("").c_str()) << output << "\n";
}




