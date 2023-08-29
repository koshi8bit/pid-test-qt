#ifndef HOTSPOTMAP_H
#define HOTSPOTMAP_H

#include <QObject>
#include <lib/koshi8bit/ui/qcustomplot/qcustomplot.h>
#include "hotspot.h"

class HotSpotMap : public QCPColorMap
{
    Q_OBJECT
public:
    explicit HotSpotMap(QCPAxis *keyAxis, QCPAxis *valueAxis);
    virtual ~HotSpotMap();
    void setSize(int width, int height);
    void setRanges(QCPRange xRange,QCPRange yRange);
    void addHotSpot(HotSpot* hs);
    void addNewHotSpot(double x, double y, double r, double A = 0.0);
    void reculcPic();
    void rescaleAndReplot();
    QList<HotSpot*> hotSpots;
private:
    double maxV = 0;
signals:

};

#endif // HOTSPOTMAP_H
