
#ifndef PID_H
#define PID_H




class PID
{
public:
    PID(double deltaT, double min, double max, double p=0, double i=0, double d=0);

    void setP(double p);
    void setI(double i);
    void setD(double d);

    double calc(double start, double setpoint);




private:
    double deltaT, min, max, p=0, i=0, d=0, prev_error=0, integral=0;
};

#endif // PID_H
