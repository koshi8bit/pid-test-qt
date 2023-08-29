#include "radarplot.h"

RadarPlot::RadarPlot(QWidget *parent)
    :AbstractPlot(parent)
{
    qcp()->replot();
}

QPointF RadarPlot::toPolar(double r, double angle)
{
    auto angleDegree = angle*M_PI/180.0;
    return QPointF(r*qCos(angleDegree), r*qSin(angleDegree));
}

RadarGraph *RadarPlot::addGraph(const QString &label, const QString &postfix, int precision, bool scientificNotation, int width)
{
    auto graph = new RadarGraph(label,
                                   postfix,
                                   colorSetter.getColor(),
                                   qcp(),
                                   precision,
                                   scientificNotation,
                                   width);
    addAbstractGraph(graph);
    return graph;
}
