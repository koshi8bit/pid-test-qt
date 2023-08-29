#ifndef ERRORXYGRAPH_H
#define ERRORXYGRAPH_H

#include "errorygraph.h"

class ErrorXYGraph : public ErrorYGraph
{
public:
    ErrorXYGraph(const QString &label, const QString &postfix, QColor color,
                 QCustomPlot *qcp, QCPAxis *yAxis, int precision = 3,
                 bool scientificNotation = false);

    void addData(double x, double y, double errorBottom, double errorTop, double errorLeft, double errorRight);
    QList<double> value(int index);

protected:
    QCPErrorBars *errorBarsX;
    QVector<double> errorsXLeft, errorsXRight;

    // AbstractGraph interface
protected:
    void updateLegendItem() override;
    void abstractSetVisible() override;
    void abstractSetColor() override;
};

#endif // ERRORXYGRAPH_H
