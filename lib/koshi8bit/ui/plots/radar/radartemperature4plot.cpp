#include "radartemperature4plot.h"

RadarTemperature4Plot::RadarTemperature4Plot(QWidget *parent)
    :RadarPlot(parent)
{
//    plot->setInteraction(QCP::iRangeZoom, true);
//    plot->setInteraction(QCP::iRangeDrag, true);
//    _qcp->axisRect()->setupFullAxesBox();

    maxDiameter = 4;


    criticalCircle = drawCircle(maxDiameter, QColor("#FF0000")); //FF0000
    drawCircle(maxDiameter, QColor("#FFAAAA"));
    drawCircle(maxDiameter*0.75, QColor("#AAFFAA"));
    drawCircle(maxDiameter*0.50, QColor("#AAFFAA"));
    drawCircle(maxDiameter*0.25, QColor("#AAAAFF"));

    qcp()->xAxis->setRange(-maxDiameter, maxDiameter);
    qcp()->yAxis->setRange(-maxDiameter, maxDiameter);

    configureLines(maxDiameter);
    qcp()->replot();
}

RadarTemperature4Graph *RadarTemperature4Plot::addGraph(const QString &label,
    ChannelDouble *up, ChannelDouble *right, ChannelDouble *down,
    ChannelDouble *left, int precision, int lineWidth)
{
    auto graph = new RadarTemperature4Graph(label,
                                colorSetter.getColor(),
                                qcp(),
                                up, right, down, left,
                                precision,
                                false,
                                lineWidth);
    addAbstractGraph(graph);
    return graph;
}

void RadarTemperature4Plot::replot()
{
    double max=0;
    foreach(auto graph, graphs())
    {
        if (!graph->visible())
            continue;

        auto isRadarTemperature4Graph =
                dynamic_cast<RadarTemperature4Graph*>(graph) != nullptr;

        if (!isRadarTemperature4Graph)
            continue;

        max = qMax(graphCast(graph)->radius(), max);
    }

    max = qMax(max, maxDiameter);

    qcp()->xAxis->setRange(-max, max);
    qcp()->yAxis->setRange(-max, max);

    criticalCircle->topLeft->setCoords(-max, -max);
    criticalCircle->bottomRight->setCoords(max, max);

    qcp()->replot();
}

RadarTemperature4Graph *RadarTemperature4Plot::graphCast(AbstractGraph *graph)
{
    return static_cast<RadarTemperature4Graph *>(graph);
}

QCPItemEllipse *RadarTemperature4Plot::drawCircle(double radius, QColor color)
{
    auto ellipse = new QCPItemEllipse(_qcp);
    ellipse->topLeft->setCoords(-radius, -radius);
    ellipse->bottomRight->setCoords(radius, radius);
    ellipse->setBrush(color);
    return ellipse;
}

void RadarTemperature4Plot::configureLines(double maxDiameter)
{
    QCPItemLine *hLine = new QCPItemLine(_qcp);
    hLine->start->setCoords(-maxDiameter, 0);
    hLine->end->setCoords(maxDiameter, 0);

    QCPItemLine *vLine = new QCPItemLine(_qcp);
    vLine->start->setCoords(0, -maxDiameter);
    vLine->end->setCoords(0, maxDiameter);

    QCPItemLine *line45 = new QCPItemLine(_qcp);
    line45->start->setCoords(toPolar(maxDiameter, 45));
    line45->end->setCoords(toPolar(maxDiameter, 180+45));

    QCPItemLine *line135 = new QCPItemLine(_qcp);
    line135->start->setCoords(toPolar(maxDiameter, 135));
    line135->end->setCoords(toPolar(maxDiameter, 180+135));
}
