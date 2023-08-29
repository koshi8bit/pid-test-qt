#ifndef AXISTIMECONFIG_H
#define AXISTIMECONFIG_H

#include <QDialog>
#include <lib/koshi8bit/ui/qcustomplot/qcustomplot.h>

//#include <lib/koshi8bit/ui/realtimeqcp/realtimeqcp.h>
#include <lib/koshi8bit/easyliving.h>

namespace Ui {
class AxisTimeConfig;
}

class AxisTimeConfig : public QDialog
{
    Q_OBJECT



public:
    explicit AxisTimeConfig(QCPAxis *axis, QWidget *parent = nullptr);
    ~AxisTimeConfig();


private slots:
    void on_buttonBox_accepted();


    void on_spinBoxFullSec_valueChanged(int arg1);
    void spinBoxDaysHoursMinutesSecondsValueChanged(int arg1);

    void on_pushButtonTime010000_clicked();
    void on_pushButtonTime001000_clicked();
    void on_pushButtonTime000500_clicked();
    void on_pushButtonTime000100_clicked();
    void on_pushButtonTime000030_clicked();


    void on_pushButtonTime003000_clicked();

private:
    Ui::AxisTimeConfig *ui;
    QCPAxis *axis;
    const int dayToSecond = 24 * 60 * 60;
    //RealTimeQCP *plot;


};

#endif // AXISTIMECONFIG_H
