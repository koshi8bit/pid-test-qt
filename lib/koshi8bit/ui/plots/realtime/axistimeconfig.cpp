#include "axistimeconfig.h"
#include "ui_axistimeconfig.h"

AxisTimeConfig::AxisTimeConfig(QCPAxis *axis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisTimeConfig)
{
    ui->setupUi(this);

    this->axis = axis;


    ui->lineEditLabel->setText(axis->label());

    // { TESTS


    // } TESTS


    ui->labelLabel->setVisible(false);
    ui->lineEditLabel->setVisible(false);

    ui->spinBoxFullSec->setValue(static_cast<int>(axis->range().upper - axis->range().lower));
    connect(ui->spinBoxDays, SIGNAL(valueChanged(int)), this, SLOT(spinBoxDaysHoursMinutesSecondsValueChanged(int)));
    connect(ui->spinBoxHours, SIGNAL(valueChanged(int)), this, SLOT(spinBoxDaysHoursMinutesSecondsValueChanged(int)));
    connect(ui->spinBoxMinutes, SIGNAL(valueChanged(int)), this, SLOT(spinBoxDaysHoursMinutesSecondsValueChanged(int)));
    connect(ui->spinBoxSeconds, SIGNAL(valueChanged(int)), this, SLOT(spinBoxDaysHoursMinutesSecondsValueChanged(int)));

    resize(450, 110);
}

AxisTimeConfig::~AxisTimeConfig()
{
    delete ui;
}

void AxisTimeConfig::on_buttonBox_accepted()
{
    //qDebug() << size();

    axis->setLabel(ui->lineEditLabel->text());

    axis->setRangeLower(axis->range().upper - ui->spinBoxFullSec->value());
    accept();
}

void AxisTimeConfig::on_spinBoxFullSec_valueChanged(int arg1)
{
    QTime t = QTime(0, 0, 0).addSecs(arg1);
    ui->spinBoxDays->setValue(arg1 / dayToSecond);
    ui->spinBoxHours->setValue(t.hour());
    ui->spinBoxMinutes->setValue(t.minute());
    ui->spinBoxSeconds->setValue(t.second());
}

void AxisTimeConfig::spinBoxDaysHoursMinutesSecondsValueChanged(int arg1)
{
    Q_UNUSED(arg1)
    QTime t = QTime(ui->spinBoxHours->value(),
                    ui->spinBoxMinutes->value(),
                    ui->spinBoxSeconds->value());

    auto sec = -t.secsTo(QTime(0, 0, 0));
    sec += ui->spinBoxDays->value() * dayToSecond;

    ui->spinBoxFullSec->setValue(sec);
}

void AxisTimeConfig::on_pushButtonTime010000_clicked()
{
    ui->spinBoxFullSec->setValue(3600);
    on_buttonBox_accepted();
}

void AxisTimeConfig::on_pushButtonTime003000_clicked()
{
    ui->spinBoxFullSec->setValue(1800);
    on_buttonBox_accepted();
}

void AxisTimeConfig::on_pushButtonTime001000_clicked()
{
    ui->spinBoxFullSec->setValue(600);
    on_buttonBox_accepted();
}

void AxisTimeConfig::on_pushButtonTime000500_clicked()
{
    ui->spinBoxFullSec->setValue(300);
    on_buttonBox_accepted();
}

void AxisTimeConfig::on_pushButtonTime000100_clicked()
{
    ui->spinBoxFullSec->setValue(60);
    on_buttonBox_accepted();
}

void AxisTimeConfig::on_pushButtonTime000030_clicked()
{
    ui->spinBoxFullSec->setValue(30);
    on_buttonBox_accepted();
}



