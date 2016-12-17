#include <cmath>

#include "WheelEncoder.h"

WheelEncoder::WheelEncoder() {

    this->initialized = false;
    this->leftWheelUpdated = false;
    this->rightWheelUpdated = false;
    this->x = 0;
    this->y = 0;
    this->theta = 0;
    this->t = 0;
    this->v = 0;
    this->omega = 0;
    this->lt = -1;
    this->rt = -1;
    this->lv = 0;
    this->rv = 0;
    this->Rw = 0.064;
    this->Lb = 0.145;
    this->er = 20;
    this->ar = M_PI/this->er;

}

bool WheelEncoder::checkInputValidity(std::vector<double> reading) {

    return reading.size() == 4 ? true : false;
}

void WheelEncoder::update(std::vector<double> reading) {

    if((int) reading[2] == 0) {
        if(lt < 0) {
            lt = reading[1];
            return;
        }
        updateLeftWheel(reading);
    } else {
        if(rt < 0) {
            rt = reading[1];
            return;
        }
        updateRightWheel(reading);
    }

    if(leftWheelUpdated && rightWheelUpdated) {
        updateRoverPositionState(reading[1]);
        leftWheelUpdated = false;
        rightWheelUpdated = false;
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

void WheelEncoder::updateLeftWheel(std::vector<double> reading) {

    lv = ar/(reading[1] - lt) * ((int) reading[3] == 1 ? 1 : -1) * Rw;
    lt = reading[1];
    leftWheelUpdated = true;
}

void WheelEncoder::updateRightWheel(std::vector<double> reading) {

    rv = ar/(reading[1] - rt) * ((int) reading[3] == 1 ? 1 : -1) * Rw;
    rt = reading[1];
    rightWheelUpdated = true;
}

void WheelEncoder::updateRoverPositionState(double t_cur) {

    double v_cur = (lv + rv)/2;
    double omega_cur = (rv-lv)/Lb;

    if(!initialized) {
        v = v_cur;
        omega = omega_cur;
        t = t_cur;
        initialized = true;
        return;
    }

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
