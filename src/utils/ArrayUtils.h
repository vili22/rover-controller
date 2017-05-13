#ifndef UTILS_ARRAYUTILS_H_
#define UTILS_ARRAYUTILS_H_

#include <vector>

using namespace std;
namespace utils {

template<class FloatType> void print_float_type_array(
		std::vector<std::vector<FloatType>> array) {

	for (typename vector<vector<FloatType>>::iterator it = array.begin();
			it != array.end(); ++it) {
		for (typename vector<FloatType>::iterator it2 = (*it).begin();
				it2 != (*it).end(); ++it2) {
			cout << *(it2) << " ";
		}
		cout << "\n";
	}
}

template<class FloatType> void convert_vector_array_to_array(FloatType *array,
		std::vector<std::vector<FloatType>> vectorArray) {

	int rowSize = vectorArray.at(0).size();

	for (size_t k = 0; k < vectorArray.size(); k++) {
		for (size_t l = 0; l < vectorArray.at(0).size(); l++) {
			array[k * rowSize + l] = vectorArray[k][l];
		}
	}
}
}



#endif /* UTILS_ARRAYUTILS_H_ */
