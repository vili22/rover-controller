/*
 * StringUtils.h
 *
 *  Created on: Aug 21, 2016
 *      Author: vvirkkal
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <vector>
#include <string>

namespace utils {

	std::vector<std::string> strSplit(std::string line);

template<class FloatType> std::vector<FloatType> convert_to_float_type(
		std::vector<std::string> values) {

	std::vector<FloatType> floatValues;
	for (std::string &s : values) {

		floatValues.push_back(std::stod(s));
	}

	return floatValues;
}

}


#endif /* STRINGUTILS_H_ */
