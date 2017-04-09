#ifndef WHEELENCODER_H
#define WHEELENCODER_H

#include <Eigen/Dense>

#include "BasicSensor.h"

class WheelEncoder : public BasicSensor {
    public:
        WheelEncoder();
        bool checkInputValidity(std::vector<double> reading);
        void update(std::vector<double> reading);
        std::vector<double> getRoverPositionState();
        std::vector<int> getTotalTicks();
    private:

        void updateLeftWheel(double t_cur);
        void updateRightWheel(double t_cur);
        void updateRoverPositionState(double t_cur);
        std::vector<double> rk4Update(double dt);

        bool initialized, leftWheelUpdated, rightWheelUpdated;
        double x, y, theta, t;
        double v, omega;
        double lt, rt;      //last time left (l) or right (r) was updated
        double lv, rv;      //velocity of the left/rigth wheel
        double Rw, Lb;      //radius of the wheel (Rw) and base length (Lb)
        double er, ar;      //encoder resolution, i.e., how many ticks per round and angular resolution
        double updateInterval;
        double left_ticks, right_ticks;
        int l_tot, r_tot;
};

#endif // WHEELENCODER_H
