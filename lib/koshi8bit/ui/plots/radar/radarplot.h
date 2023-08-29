#ifndef RADARPLOT_H
#define RADARPLOT_H

#include <lib/koshi8bit/ui/plots/base/abstractplot.h>
#include <lib/koshi8bit/ui/plots/radar/radargraph.h>

class RadarPlot : public AbstractPlot
{
public:
    RadarPlot(QWidget *parent);
    static QPointF toPolar(double r, double angle);

    RadarGraph *addGraph(const QString &label, const QString &postfix = "",
                         int precision = 3, bool scientificNotation = false, int width = 1);

private:
    QCPItemEllipse *criticalCircle;

    QCPItemEllipse *drawCircle(double radius, QColor color);
    void configureLines(double maxDiameter);




};

#endif // RADARPLOT_H
