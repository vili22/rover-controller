#include <cmath>
#include <iostream>
#include "WheelEncoder.h"
#include "Configuration.h"

using namespace std;
using namespace configuration;

WheelEncoder::WheelEncoder() {

    this->initialized = false;
    this->leftWheelUpdated = false;
    this->rightWheelUpdated = false;
    this->left_ticks = 0;
    this->right_ticks = 0;
    this->x = 0;
    this->y = 0;
    this->theta = 0;
    this->t = -1;
    this->v = 0;
    this->omega = 0;
    this->lt = -1;
    this->rt = -1;
    this->lv = 0;
    this->rv = 0;
    this->Rw = Configuration::getInstance()->getConfigurationFloat("WHEEL_DIAMETER");
    this->Lb = Configuration::getInstance()->getConfigurationFloat("BASE_LENGTH");
    this->er = Configuration::getInstance()->getConfigurationFloat("ENCODER_RESOLUTION");
    this->ar = 2 * M_PI/this->er;
    this->updateInterval = Configuration::getInstance()->getConfigurationFloat("ENCODER_UPDATE_INTERVAL");
    this->l_tot = 0;
    this->r_tot = 0;

}

bool WheelEncoder::checkInputValidity(std::vector<double> reading) {

    return reading.size() == 4 ? true : false;
}

void WheelEncoder::update(std::vector<double> reading) {

    if(t < 0) {
        t = reading[1];
        return;
    }

    if((int) reading[2] == 0) {
        if(reading[1] - lt  > 0.015) {
            lt = reading[1];
            left_ticks += ((int) reading[3] == 1 ? 1 : -1);
            l_tot++;
        } else {
            return;
        }
    } else {
        if(reading[1] - rt  > 0.015) {
            rt = reading[1];
            right_ticks += ((int) reading[3] == 1 ? 1 : -1);
            r_tot++;
        } else {
            return;
        }
    }



    if(reading[1] - t > updateInterval) {
        updateLeftWheel(reading[1]);
        updateRightWheel(reading[1]);
        updateRoverPositionState(reading[1]);
    }
}

std::vector<double> WheelEncoder::getRoverPositionState() {

    std::vector<double> state;
    state.push_back(x);
    state.push_back(y);
    state.push_back(theta);
    state.push_back(t);
    return state;
}

std::vector<int> WheelEncoder::getTotalTicks() {

    vector<int> ticks;
    ticks.push_back(l_tot);
    ticks.push_back(r_tot);

    return ticks;
}

void WheelEncoder::updateLeftWheel(double t_cur) {

    lv = ar/(t_cur - t) * left_ticks *  Rw;
    left_ticks = 0;
}

void WheelEncoder::updateRightWheel(double t_cur) {

    rv = ar/(t_cur - t) * right_ticks * Rw;
    right_ticks = 0;
}

void WheelEncoder::updateRoverPositionState(double t_cur) {

    v = (lv + rv)/2;
    omega = (rv-lv)/Lb;
  //  std::cout << "left speed :" << lv << " right speed: " << rv << "speed: " << v << " omega: " << omega << "\n";
//    if(!initialized) {
//        v = v_cur;
//        omega = omega_cur;
//        t = t_cur;
//        initialized = true;
//        return;
//    }

    double dt = t_cur - t;
    std::vector<double> rk4Vector = rk4Update(dt);

    x = x + dt/6 * rk4Vector[0];
    y = y + dt/6 * rk4Vector[1];
    theta = theta + dt/6 * rk4Vector[2];
    t = t_cur;
}

std::vector<double> WheelEncoder::rk4Update(double dt) {

    double k00 = v * cos(theta);
    double k01 = v * sin(theta);
    double k02 = omega;

    double k10 = v * cos(theta + dt/2 * k02);
    double k11 = v * sin(theta + dt/2 * k02);
    double k12 = omega;

    double k20 = v * cos(theta + dt/2 * k12);
    double k21 = v * sin(theta + dt/2 + k12);
    double k22 = omega;

    double k30 = v * cos(theta + dt * k22);
    double k31 = v * sin(theta + dt * k22);
    double k32 = omega;

    std::vector<double> updateVector;
    updateVector.push_back(k00 + 2 * (k10 + k20) + k30);
    updateVector.push_back(k01 + 2 * (k11 + k21) + k31);
    updateVector.push_back(k02 + 2 * (k12 + k22) + k32);

    return updateVector;
}
