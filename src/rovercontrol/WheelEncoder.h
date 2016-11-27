#ifndef WHEELENCODER_H
#define WHEELENCODER_H

#include "BasicSensor.h"

class WheelEncoder : public BasicSensor {
    public:
        WheelEncoder();
        bool checkInputValidity(std::vector<double> reading);
        void update(std::vector<double> reading);
    private:
};

#endif // WHEELENCODER_H
