#ifndef HOTSPOT_H
#define HOTSPOT_H

class HotSpot
{
public:
    explicit HotSpot(double x, double y, double r, double A = 0.0);
    double x;
    double y;
    double r;
    double A;
};

#endif // HOTSPOT_H
