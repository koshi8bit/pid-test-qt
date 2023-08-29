#include "minmax.h"
#include "ui_minmax.h"

MinMax::MinMax(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinMax)
{
    ui->setupUi(this);
    setVisibleEdits(false);
}

MinMax::~MinMax()
{
    delete ui;
}

void MinMax::setComponentsEnabled(bool enabled)
{
    ui->pushButtonConfig->setEnabled(enabled);
    if (!enabled)
    {
        ui->pushButtonConfig->setChecked(false);
        //setVisibleEdits(false);
    }
}

void MinMax::setRange(double min, double max)
{
    ui->doubleSpinBoxMin->setValue(min);
    ui->doubleSpinBoxMax->setValue(max);
}

void MinMax::on_doubleSpinBoxMin_valueChanged(double arg1)
{
    emit rangeChanged(arg1, ui->doubleSpinBoxMax->value());
}

void MinMax::on_doubleSpinBoxMax_valueChanged(double arg1)
{
    emit rangeChanged(ui->doubleSpinBoxMin->value(), arg1);
}

void MinMax::setVisibleEdits(bool newValue)
{
    ui->labelMin->setVisible(newValue);
    ui->doubleSpinBoxMin->setVisible(newValue);
    ui->labelMax->setVisible(newValue);
    ui->doubleSpinBoxMax->setVisible(newValue);
}

void MinMax::on_pushButtonConfig_toggled(bool checked)
{
    setVisibleEdits(checked);
}
