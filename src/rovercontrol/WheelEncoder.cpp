#include "WheelEncoder.h"

WheelEncoder::WheelEncoder() {

}

void WheelEncoder::update(std::vector<double> reading) {

}

bool WheelEncoder::checkInputValidity(std::vector<double> reading) {

    return reading.size() == 4 ? true : false;
}
