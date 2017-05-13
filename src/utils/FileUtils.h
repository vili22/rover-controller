#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
namespace utils {

template<class FloatType> vector<vector<FloatType>> read_float_type_array(
		const string filename) {

	ifstream input;
	string line;
	vector < vector < FloatType >> floatArray;
	input.open(filename.c_str());
	if (!input.is_open()) {
		return floatArray;
	}

	while (getline(input, line)) {
		istringstream numberStream(line);
		vector<FloatType> lineValues;
		FloatType value;
		while (numberStream >> value) {
			lineValues.push_back(value);
		}
		floatArray.push_back(lineValues);
	}
	return floatArray;
}

}


#endif // FILEUTILS_H_
