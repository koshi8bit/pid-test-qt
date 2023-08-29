#include "simplegraph.h"

SimpleGraph::SimpleGraph(const QString &label, const QString &postfix, QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision, bool scientificNotation)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{
    _yAxis = yAxis;
    _graph = qcp->addGraph(qcp->xAxis, yAxis);
    _graph->setName(label);

    _graph->setLineStyle(QCPGraph::LineStyle::lsNone);
    _graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 6));
    _graph->setAdaptiveSampling(true);


    QPen pen;
    pen.setColor(color);
    pen.setWidth(1);
    _graph->setPen(pen);
    _graph->setBrush(color);

}

//SimpleGraph::~SimpleGraph()
//{

//}

void SimpleGraph::addData(double x, double y)
{
    if (_graph)
        _graph->addData(x, y);
}

void SimpleGraph::updateLegendItem()
{
}

void SimpleGraph::abstractSetVisible()
{
    _graph->setVisible(visible());

}

void SimpleGraph::abstractSetColor()
{
    _graph->setPen(color());
    _graph->setBrush(color());


}
