/*
 * StringUtils.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: vvirkkal
 */

#include <sstream>

#include "StringUtils.h"


std::vector<std::string> utils::strSplit(std::string line) {

	std::vector<std::string> splitString;
	std::stringstream instream(line);
	std::string tempString;


	while(instream.good()) {

		instream >> tempString;
		splitString.push_back(tempString);
	}

	return splitString;
}





