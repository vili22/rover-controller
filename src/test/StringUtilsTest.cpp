/*
 * StringUtilsTest.cpp
 *
 *  Created on: Aug 27, 2016
 *      Author: vvirkkal
 */
#include "gtest/gtest.h"

#include "StringUtils.h"


TEST(StringUtilsTest, strSplit) {

	std::string line = "1.432112 0 1.123123 1.341412 1.212112";
	std::vector<std::string> splitted = utils::strSplit(line);
	EXPECT_NE(std::stod(splitted.at(0)), 1.43112);
}


