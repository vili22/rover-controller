/*
 * GeometryUtils.h
 *
 *  Created on: May 22, 2017
 *      Author: vvirkkal
 */

#ifndef UTILS_GEOMETRYUTILS_H_
#define UTILS_GEOMETRYUTILS_H_

#include <vector>
#include <cmath>

using namespace std;

namespace geometryutils {

template<class FloatType> FloatType pointDistance(vector<FloatType> p1,
		vector<FloatType> p2) {

	return sqrt(
			pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2)
					+ pow(p1[2] - p2[2], 2));
}

}


#endif /* UTILS_GEOMETRYUTILS_H_ */
