/*
 * WheelEncoderTest.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: vvirkkal
 */

#include <iomanip>

#include "gtest/gtest.h"

#include "FileUtils.h"


TEST(WheelEncoderTest, wheelEncoder) {

	std::string filename = "/home/vvirkkal/Documents/development/rover-controller/sensor-data/data.txt";
	std::vector<std::vector<double>> doubleArray = utils::parse_sensor_data(filename);

	testing::internal::CaptureStdout();

	std::cout << std::fixed;
	std::cout << std::setprecision(6);
	for(std::vector<std::vector<double>>::iterator it = doubleArray.begin(); it < doubleArray.end(); it++) {
		for(size_t index = 0; index < (*it).size(); index++) {
			std::cout << (*it)[index] << " ";
		}
		std::cout << "\n";
	}

    std::string output = testing::internal::GetCapturedStdout();
	ASSERT_STREQ(output.c_str(), std::string("").c_str()) << output << "\n";
}




