#ifndef BASICSENSOR_H
#define BASICSENSOR_H

#include <vector>

class BasicSensor
{
    public:
        BasicSensor();

        virtual bool checkInputValidity(std::vector<double> reading) = 0;
        virtual void update(std::vector<double> reading) = 0;

    private:
        double prevTimeStamp;
};

#endif // BASICSENSOR_H
