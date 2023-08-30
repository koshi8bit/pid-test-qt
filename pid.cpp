
#include "pid.h"

PID::PID(double deltaT, double min, double max, double p, double i, double d)
{
    this->deltaT = deltaT;
    this->min = min;
    this->max = max;
    this->p = p;
    this->i = i;
    this->d = d;
}

void PID::setP(double p)
{
    this->p = p;
}

void PID::setI(double i)
{
    this->i = i;
}

void PID::setD(double d)
{
    this->d = d;
}

double PID::calc(double currentVal, double target)
{
    double error = target - currentVal;

    double Pout = p * error;

    integral += error * deltaT;
    double Iout = i * integral;

    double derivative = (error - prev_error) / deltaT;
    double Dout = d * derivative;

    double output = Pout + Iout + Dout;

    if (output > max)
        output = max;

    if (output < min)
        output = min;

    prev_error = error;

    return output;
}

void PID::reset()
{
    prev_error = 0;
    integral = 0;
}
