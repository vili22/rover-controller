/*
 * StringUtils.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: vvirkkal
 */

#include <sstream>

#include "StringUtils.h"

using namespace std;

vector<string> utils::strSplit(string line) {

	vector<string> splitString;
	stringstream instream(line);
	string tempString;


	while(instream.good()) {

		instream >> tempString;
		splitString.push_back(tempString);
	}

	return splitString;
}





