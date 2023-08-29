#include "hotspotmap.h"

HotSpotMap::HotSpotMap(QCPAxis *keyAxis, QCPAxis *valueAxis) : QCPColorMap(keyAxis,valueAxis)
{

}

HotSpotMap::~HotSpotMap()
{
    foreach(HotSpot *hs, hotSpots){
        delete hs;
    }
}

void HotSpotMap::setSize(int width, int height)
{
    this->data()->setSize(width,height);

}

void HotSpotMap::setRanges(QCPRange xRange, QCPRange yRange)
{
    this->data()->setRange(xRange,yRange);
}

void HotSpotMap::addHotSpot(HotSpot *hs)
{
    hotSpots.append(hs);
}

void HotSpotMap::addNewHotSpot(double x, double y, double r, double A)
{
    hotSpots.append(new HotSpot(x,y,r,A));
}

void HotSpotMap::reculcPic()
{
    maxV = 0;
    for(int x = 0; x < this->data()->keySize(); x++){
        for(int y = 0; y < this->data()->valueSize(); y++){
            double xV = 0;
            double yV = 0;
            double total = 0;
            double desc = 1;
            this->data()->cellToCoord(x,y,&xV,&yV);
            foreach(HotSpot *hs, hotSpots){
                desc = (2.0*hs->r*hs->r);
                total += hs->A * exp(-( powf(xV-hs->x,2.0)/desc + powf(yV-hs->y,2.0)/desc));
            }
            if(total > maxV){
                maxV = total;
            }
            this->data()->setCell(x,y,total);
        }
    }
}

void HotSpotMap::rescaleAndReplot()
{
    this->colorScale()->setDataRange(QCPRange(0,maxV));
    this->parentPlot()->replot();
}
