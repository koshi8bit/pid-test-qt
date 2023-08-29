#ifndef RADARTEMPERATURE4PLOT_H
#define RADARTEMPERATURE4PLOT_H

#include "radarplot.h"
#include "radartemperature4graph.h"

class RadarTemperature4Plot : public RadarPlot
{
public:
    RadarTemperature4Plot(QWidget *parent);

    RadarTemperature4Graph *addGraph(const QString &label,
                         ChannelDouble *up, ChannelDouble *right,
                         ChannelDouble *down, ChannelDouble *left,
                         int precision = 1,
                         int lineWidth = 5);

    void replot();

private:
    RadarTemperature4Graph* graphCast(AbstractGraph* graph);
    double maxDiameter = 2;

    QCPItemEllipse *criticalCircle;

    QCPItemEllipse *drawCircle(double radius, QColor color);
    void configureLines(double maxDiameter);
};

#endif // RADARTEMPERATURE4PLOT_H
