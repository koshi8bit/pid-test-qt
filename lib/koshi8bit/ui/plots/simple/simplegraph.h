#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <lib/koshi8bit/ui/plots/base/abstractgraph.h>

class SimpleGraph: public AbstractGraph
{
public:
    SimpleGraph(const QString &label, const QString &postfix, QColor color,
                QCustomPlot *qcp, QCPAxis *yAxis, int precision = 3,
                bool scientificNotation = false);

    //~SimpleGraph() override;
    void addData(double x, double y);


private:


    // AbstractGraph interface
protected:
    QCPAxis *_yAxis;
    QCPGraph *_graph;

    void updateLegendItem() override;
    void abstractSetVisible() override;
    void abstractSetColor() override;
};


#endif // SIMPLEGRAPH_H
