/*
 * Quaternions.cpp
 *
 *  Created on: Jun 30, 2016
 *      Author: vvirkkal
 */

#include <cmath>
#include <limits>

#include "Quaternions.h"

Eigen::Quaterniond Quaternions::init(double *array) {

	return Eigen::Quaterniond(array);
}


Eigen::Quaternion<double> Quaternions::initFromVectors(Eigen::Vector3d a, Eigen::Vector3d b) {

	Eigen::Quaterniond quat = Eigen::Quaterniond::FromTwoVectors(a, b);
	quat.normalize();
	return quat;
}


Eigen::Matrix3d Quaternions::quaternionToRotationMatrix(Eigen::Quaterniond quat) {

	quat.normalize();
	return quat.toRotationMatrix();
}

Eigen::Vector3d rotateVector(Eigen::Vector3d vec, Eigen::Quaterniond quat) {

	return Quaternions::quaternionToRotationMatrix(quat) * vec;
}

Eigen::Quaterniond Quaternions::gyroUpdate(Eigen::Quaterniond quat, double *gyro, double dt) {

	double newComponents[4];
	double gyroScaled[] = {gyro[0] * 0.5 * dt, gyro[1] * 0.5 * dt, gyro[2] * 0.5 * dt};
	double gyroScaledSq = gyroScaled[0] * gyroScaled[0] + gyroScaled[1] * gyroScaled[1] +
			gyroScaled[2] * gyroScaled[2];

	double s;

	if(gyroScaledSq * gyroScaledSq / 24.0 < std::numeric_limits<double>::epsilon()) {

		newComponents[0] = 1.0 - gyroScaledSq/2.0;
		s = 1.0 - gyroScaledSq/6.0;
	} else {

		double gyroScaleNorm = sqrt(gyroScaledSq);
		newComponents[0] = cos(gyroScaleNorm);
		s = sin(gyroScaleNorm) / gyroScaleNorm;
	}

	newComponents[1] = gyroScaled[0] * s;
	newComponents[2] = gyroScaled[1] * s;
	newComponents[3] = gyroScaled[2] * s;

	return Eigen::Quaterniond(newComponents) * quat;
}

