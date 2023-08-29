#ifndef GRADIENTLINEEDITWIDGET_H
#define GRADIENTLINEEDITWIDGET_H

#include <QWidget>

#include <lib/koshi8bit/ui/qcustomplot/qcustomplot.h>

namespace Ui {
class MinMax;
}

class MinMax : public QWidget
{
    Q_OBJECT

public:
    explicit MinMax(QWidget *parent = nullptr);
    ~MinMax();

    void setComponentsEnabled(bool enabled);



signals:
    void rangeChanged(double min, double max);

public slots:
    void setRange(double min, double max);

private slots:
    void on_doubleSpinBoxMin_valueChanged(double arg1);
    void on_doubleSpinBoxMax_valueChanged(double arg1);

    void on_pushButtonConfig_toggled(bool checked);

private:
    Ui::MinMax *ui;

    void setVisibleEdits(bool newValue);
};

#endif // GRADIENTLINEEDITWIDGET_H
