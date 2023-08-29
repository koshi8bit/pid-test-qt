#ifndef REALTIMEGRAPH_H
#define REALTIMEGRAPH_H

#include <lib/koshi8bit/ui/plots/base/abstractgraph.h>

class RealTimeGraph: public AbstractGraph
{
public:
    RealTimeGraph(const QString &label, const QString &postfix, QColor color,
                  QCustomPlot *qcp, QCPAxis *yAxis, int precision = 3,
                  bool scientificNotation = false);
    ~RealTimeGraph() override;

    //TODO ?rename to qcpGraph
    QCPGraph *graph();

    //void addData(double valueCursor);
    void addData(double key, double valueCursor);

    double valueCursor();
    double valueLast();

    void updateValue();
    void moveCursor(double key);
    void moveCursor2(double key);
    void setCursor2Visible(bool newValue);


private:
    double avg;
    double calcAvg();
    double _valueCursor;
    //ValueScaler valueScaler;
    QCPAxis *_yAxis;

    QCPGraph *_graph;

    void configureCursor(QCPItemTracer **cursor);
    QCPItemTracer *_cursor, *_cursor2;

    // AbstractGraph interface
protected:
    void updateLegendItem() override;
    void abstractSetVisible() override;
    void abstractSetColor() override;
};

#endif // REALTIMEGRAPH_H
