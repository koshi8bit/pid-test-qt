#ifndef GRADIENTLINEEDIT_H
#define GRADIENTLINEEDIT_H

#include <QObject>
#include <QLineEdit>

#include <lib/koshi8bit/ui/qcustomplot/qcustomplot.h>

#include <lib/koshi8bit/easyliving.h>

class GradientLineEdit : public QLineEdit
{
public:
    GradientLineEdit(QWidget *parent);

    void configure(QCPRange *range, QCPColorGradient *gradient);
    void configure();
    void configureRange();
    void configureGradient();
    void setMinMax(double min, double max);
    void setRange(QCPRange *range, bool deleteOld = true);
    void setGradient(QCPColorGradient *gradient, bool deleteOld = true);

    double min();
    double max();

private:
    QCPRange *_range = nullptr;
    QCPColorGradient *_gradient = nullptr;

    double previousValue = 0;

signals:
    void rangeChanged(double min, double max);

public slots:
    void display(double value);
};

#endif // GRADIENTLINEEDIT_H
