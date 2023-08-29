
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

double PID::calc(double start, double setpoint)
{
    // Calculate error
    double error = start - setpoint;

    // Proportional term
    double Pout = p * error;

    // Integral term
    integral += error * deltaT;
    double Iout = i * integral;

    // Derivative term
    double derivative = (error - prev_error) / deltaT;
    double Dout = d * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

    // Restrict to max/min
    if (output > max)
        output = max;

    if (output < min)
        output = min;

    // Save error to previous error
    prev_error = error;

    return output;
}
