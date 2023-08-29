#ifndef RADARGRAPH_H
#define RADARGRAPH_H

#include <lib/koshi8bit/ui/plots/base/abstractgraph.h>

class RadarGraph : public AbstractGraph
{
public:
    static QPointF toPolar(double r, double angle);
    RadarGraph(const QString &label, const QString &postfix, QColor color,
               QCustomPlot *qcp, int precision = 3,
               bool scientificNotation = false, int lineWidth = 1);

    double radius() const;
    double angle() const;

    void setWidth(int width);
    int width() const;

    void setPen();

public slots:
    void setValue(double radius, double angle);
    void setAngle(double angle);
    void setRadius(double radius);

private:
    //RadarPlot *plot;
    QCPItemLine *arrow;
    double _radius=0, _angle=0;
    int _width=1;
    void redrawArrow();


protected:
    void updateLegendItem() override;
    void abstractSetVisible() override;
    void abstractSetColor() override;
};

#endif // RADARGRAPH_H
