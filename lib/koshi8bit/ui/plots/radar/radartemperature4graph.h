#ifndef RADARTEMPERATURE4GRAPH_H
#define RADARTEMPERATURE4GRAPH_H

#include "radargraph.h"
#include <lib/koshi8bit/log/channeldouble.h>

class RadarTemperature4Graph : public RadarGraph
{
public:
    RadarTemperature4Graph(const QString &label, QColor color, QCustomPlot *qcp,
                           ChannelDouble *up, ChannelDouble *right,
                           ChannelDouble *down, ChannelDouble *left,
                           int precision = 3, bool scientificNotation = false,
                           int lineWidth = 5);

    ChannelDouble *up, *right, *down, *left;

    void calcDeviation();

    double rotationOffset() const;
    void setRrotationOffset(double rotationOffset);

    int legendPrecision() const;
    void setLegendPrecision(int legendPrecision);

private:
    double _rotationOffset=0;
    int _legendPrecision=0;


    // RadarGraph interface
private:
    void updateLegendItem() override;
};

#endif // RADARTEMPERATURE4GRAPH_H
