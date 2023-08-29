#ifndef AXISVALUECONFIG_H
#define AXISVALUECONFIG_H

#include <QDialog>
#include <lib/koshi8bit/ui/qcustomplot/qcustomplot.h>

#include <lib/koshi8bit/easyliving.h>

namespace Ui {
class AxisValueConfig;
}

class AxisValueConfig : public QDialog
{
    Q_OBJECT



public:
    explicit AxisValueConfig(QCPAxis *axis, QWidget *parent = nullptr);
    ~AxisValueConfig();


    enum AxisType
    {
        NumericStandardNotation,
        NumericScientificNotation
    };
    Q_ENUM(AxisType)


private slots:
    void on_buttonBox_accepted();

    void on_checkBoxScientificNotationAxis_toggled(bool checked);

    void on_checkBoxAutoscale_toggled(bool checked);

    void on_spinBoxNumberPrecision_valueChanged(int arg1);

    void on_pushButtonColor_clicked();

private:
    Ui::AxisValueConfig *ui;
    const QString scientificNotationFormat = "eb", standatrFormat = "f";
    QCPAxis *axis;
    AxisType axisType;
    QColor color;

};

#endif // AXISVALUECONFIG_H
