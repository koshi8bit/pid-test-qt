#include "axisvalueconfig.h"
#include "ui_axisvalueconfig.h"

AxisValueConfig::AxisValueConfig(QCPAxis *axis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisValueConfig)
{
    ui->setupUi(this);

    this->axis = axis;


    ui->lineEditLabel->setText(axis->label());

    // { TESTS


    // } TESTS

    ui->scientificNotationEditMin->setValue(axis->range().lower);
    ui->scientificNotationEditMax->setValue(axis->range().upper);
    ui->doubleSpinBoxMin->setValue(axis->range().lower);
    ui->doubleSpinBoxMax->setValue(axis->range().upper);

    ui->checkBoxScientificNotationTick->setChecked(
                axis->numberFormat() == scientificNotationFormat);


    if (axis->scaleType() == QCPAxis::ScaleType::stLogarithmic)
    {
        axisType = AxisType::NumericScientificNotation;

        ui->checkBoxScientificNotationAxis->setChecked(true);

        ui->doubleSpinBoxMin->setVisible(false);
        ui->doubleSpinBoxMax->setVisible(false);

    }
    else
    {
        axisType = AxisType::NumericStandardNotation;

        ui->checkBoxScientificNotationAxis->setChecked(false);


        ui->scientificNotationEditMin->setVisible(false);
        ui->scientificNotationEditMax->setVisible(false);

    }
    ui->spinBoxNumberPrecision->setValue(axis->numberPrecision());

    color = axis->labelColor();
    QString css = QString("background: %1;").arg(color.name());
    ui->pushButtonColor->setStyleSheet(css);

    //resize(300, 200);

}

AxisValueConfig::~AxisValueConfig()
{
    delete ui;
}

void AxisValueConfig::on_buttonBox_accepted()
{
    //qDebug() << size();

    axis->setLabel(ui->lineEditLabel->text());

    axis->setLabelColor(color);
    axis->setBasePen(QPen(color, 1));
    axis->setSubTickPen(QPen(color, 1));
    axis->setTickLabelColor(color);
    axis->setTickPen(QPen(color, 1));
    axis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    axis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    axis->grid()->setSubGridVisible(true);
    axis->grid()->setZeroLinePen(Qt::NoPen);

    if (ui->checkBoxAutoscale->isChecked())
    {
        foreach(auto graph, axis->graphs())
        {
            graph->rescaleValueAxis(false, true);
        }
        return;
    }

    axis->setNumberFormat(ui->checkBoxScientificNotationTick->isChecked()
                          ? scientificNotationFormat
                          : standatrFormat);

    if (axisType == AxisType::NumericStandardNotation)
    {
        axis->setRange(
                       ui->doubleSpinBoxMin->value(),
                       ui->doubleSpinBoxMax->value());

        axis->setScaleType(QCPAxis::stLinear);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTicker);
        axis->setTicker(ticker);
        axis->setNumberPrecision(ui->spinBoxNumberPrecision->value());


        return;
    }

    if (axisType == AxisType::NumericScientificNotation)
    {
        axis->setRange(
                       ui->scientificNotationEditMin->value(),
                       ui->scientificNotationEditMax->value());

        axis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        axis->setTicker(logTicker);
        axis->setNumberPrecision(ui->spinBoxNumberPrecision->value());

        return;
    }



}


void AxisValueConfig::on_checkBoxScientificNotationAxis_toggled(bool checked)
{
    ui->checkBoxScientificNotationTick->setChecked(checked);
    ui->checkBoxScientificNotationTick->setEnabled(!checked);

    if (checked)
    {
        axisType = AxisType::NumericScientificNotation;
        ui->doubleSpinBoxMin->setVisible(false);
        ui->doubleSpinBoxMax->setVisible(false);
        ui->scientificNotationEditMin->setVisible(true);
        ui->scientificNotationEditMax->setVisible(true);
        ui->spinBoxNumberPrecision->setValue(0);
    }
    else
    {
        axisType = AxisType::NumericStandardNotation;
        ui->doubleSpinBoxMin->setVisible(true);
        ui->doubleSpinBoxMax->setVisible(true);
        ui->scientificNotationEditMin->setVisible(false);
        ui->scientificNotationEditMax->setVisible(false);
        ui->spinBoxNumberPrecision->setValue(1);
    }

}

void AxisValueConfig::on_checkBoxAutoscale_toggled(bool checked)
{
    ui->doubleSpinBoxMin->setEnabled(!checked);
    ui->doubleSpinBoxMax->setEnabled(!checked);

    ui->scientificNotationEditMin->setEnabled(!checked);
    ui->scientificNotationEditMax->setEnabled(!checked);
}

void AxisValueConfig::on_spinBoxNumberPrecision_valueChanged(int arg1)
{
    ui->doubleSpinBoxMin->setDecimals(arg1);
    ui->doubleSpinBoxMax->setDecimals(arg1);
}

void AxisValueConfig::on_pushButtonColor_clicked()
{
    auto color = QColorDialog::getColor(axis->labelColor(), this, tr("Выберите цвет"));
    if (color.isValid())
    {
        this->color = color;
        QString css = QString("background: %1;").arg(color.name());
        ui->pushButtonColor->setStyleSheet(css);
    }
}
