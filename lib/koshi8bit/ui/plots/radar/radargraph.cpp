#include "radargraph.h"

RadarGraph::RadarGraph(const QString &label, const QString &postfix,
                       QColor color, QCustomPlot *qcp, int precision,
                       bool scientificNotation, int lineWidth)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{
    arrow = new QCPItemLine(qcp);
    //arrow->start->setAxes()
    arrow->start->setCoords(0, 0);
    setValue(0, 0);

    arrow->setHead(QCPLineEnding::esSpikeArrow);

    setPen();
    setWidth(lineWidth);
}

QPointF RadarGraph::toPolar(double r, double angle)
{
    //TODO copy from radarplot DRY
    auto angleDegree = angle*M_PI/180.0;
    return QPointF(r*qCos(angleDegree), r*qSin(angleDegree));
}


void RadarGraph::updateLegendItem()
{
    if (visible())
        _legendItem->setValue(radius());
}

void RadarGraph::setValue(double radius, double angle)
{
    _radius = radius;
    _angle = angle;

    redrawArrow();
}

int RadarGraph::width() const
{
    return _width;
}

void RadarGraph::setPen()
{
    QPen pen;
    pen.setColor(color());
    pen.setWidth(width());
    arrow->setPen(pen);
}

void RadarGraph::setWidth(int width)
{
    _width = width;
    setPen();

}

void RadarGraph::redrawArrow()
{
//        _legendItem->setValue(QString("%1 (%2)")
//                              .arg(EasyLiving::formatDouble(radius(), 1))
//                          .arg(EasyLiving::formatDouble(angle(), 0)));

    updateLegendItem();
    arrow->end->setCoords(toPolar(radius(), angle()));
}

void RadarGraph::abstractSetVisible()
{
    arrow->setVisible(visible());
    updateLegendItem();
}

void RadarGraph::abstractSetColor()
{
    setPen();
}

double RadarGraph::angle() const
{
    return _angle;
}

void RadarGraph::setAngle(double angle)
{
    _angle = angle;
    redrawArrow();
}

double RadarGraph::radius() const
{
    return _radius;
}

void RadarGraph::setRadius(double radius)
{
    _radius = radius;
    redrawArrow();
}
