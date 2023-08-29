#include "simpleplot.h"

SimplePlot::SimplePlot(QWidget *parent)
    :AbstractPlot(parent)
{
    qcp()->setInteraction(QCP::iRangeZoom, true);
    qcp()->setInteraction(QCP::iRangeDrag, true);
    configurePlotBackground(true);
}

SimpleGraph *SimplePlot::addGraph(const QString &label, const QString &postfix, bool yAxis2, int precision, bool scientificNotation)
{
    auto graph = new SimpleGraph(label,
                                 postfix,
                                 colorSetter.getColor(),
                                 qcp(),
                                 yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                                 precision,
                                 scientificNotation);
    addAbstractGraph(graph);
    return graph;
}

ErrorYGraph *SimplePlot::addGraphErrorY(const QString &label, const QString &postfix, bool yAxis2, int precision, bool scientificNotation)
{
    auto graph = new ErrorYGraph(label,
                                 postfix,
                                 colorSetter.getColor(),
                                 qcp(),
                                 yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                                 precision,
                                 scientificNotation);
    addAbstractGraph(graph);
    return graph;
}

ErrorXYGraph *SimplePlot::addGraphErrorXY(const QString &label, const QString &postfix, bool yAxis2, int precision, bool scientificNotation)
{
    auto graph = new ErrorXYGraph(label,
                                 postfix,
                                 colorSetter.getColor(),
                                 qcp(),
                                 yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                                 precision,
                                 scientificNotation);
    addAbstractGraph(graph);
    return graph;
}
