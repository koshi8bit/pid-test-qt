#ifndef SIMPLEPLOT_H
#define SIMPLEPLOT_H

#include <lib/koshi8bit/ui/plots/base/abstractplot.h>
#include <lib/koshi8bit/ui/plots/simple/simplegraph.h>
#include <lib/koshi8bit/ui/plots/simple/errorygraph.h>
#include <lib/koshi8bit/ui/plots/simple/errorxygraph.h>

class SimplePlot : public AbstractPlot
{
public:
    SimplePlot(QWidget *parent);

    SimpleGraph *addGraph(const QString &label, SimpleGraph::Style style, const QString &postfix = "", bool yAxis2 = false,
                         int precision = 3, bool scientificNotation = false);

    ErrorYGraph *addGraphErrorY(const QString &label, const QString &postfix = "", bool yAxis2 = false,
                         int precision = 3, bool scientificNotation = false);

    ErrorXYGraph *addGraphErrorXY(const QString &label, const QString &postfix = "", bool yAxis2 = false,
                         int precision = 3, bool scientificNotation = false);


private:
    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);
};

#endif // SIMPLEPLOT_H
