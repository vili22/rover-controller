/*
 * Quaternions.h
 *
 *  Created on: Jun 30, 2016
 *      Author: vvirkkal
 */

#ifndef QUATERNIONS_H_
#define QUATERNIONS_H_

#include <vector>

#include <Eigen/Dense>

namespace Quaternions {

	Eigen::Quaterniond gyroUpdate(Eigen::Quaterniond quat, double *gyro, double dt);
	Eigen::Matrix3d quaternionToRotationMatrix(Eigen::Quaterniond quat);
	Eigen::Vector3d rotateVector(Eigen::Vector3d vec, Eigen::Quaterniond quat);
	Eigen::Quaterniond init(double *array);
	Eigen::Quaterniond initFromVectors(Eigen::Vector3d a, Eigen::Vector3d b);
}


#endif /* QUATERNIONS_H_ */
