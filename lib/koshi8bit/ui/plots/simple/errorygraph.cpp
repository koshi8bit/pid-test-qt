#include "errorygraph.h"


ErrorYGraph::ErrorYGraph(const QString &label, const QString &postfix, QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision, bool scientificNotation)
    :SimpleGraph(label, postfix, color, qcp, yAxis, precision, scientificNotation)
{
    auto pen = _graph->pen();
    pen.setStyle(Qt::PenStyle::SolidLine);

    errorBarsY = new QCPErrorBars(qcp->xAxis, yAxis);
    errorBarsY->removeFromLegend();
    errorBarsY->setDataPlottable(_graph);
    errorBarsY->setPen(pen);
    errorBarsY->setErrorType(QCPErrorBars::etValueError);
    //_errorBars->setBrush(color);
}

void ErrorYGraph::addData(double x, double y, double errorBottom, double errorTop)
{
    valuesX.append(x);
    valuesY.append(y);
    errorsYTop.append(errorTop);
    errorsYBottom.append(errorBottom);

    _graph->setData(valuesX, valuesY, true);
    errorBarsY->setData(errorsYBottom, errorsYTop);

}

int ErrorYGraph::count() const
{
    return valuesX.count();
}

void ErrorYGraph::updateLegendItem()
{
    SimpleGraph::updateLegendItem();
}

void ErrorYGraph::abstractSetVisible()
{
    SimpleGraph::abstractSetVisible();
    errorBarsY->setVisible(visible());
}

void ErrorYGraph::abstractSetColor()
{
    SimpleGraph::abstractSetColor();
    errorBarsY->setPen(color());
}
