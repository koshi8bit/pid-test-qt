
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "lib/koshi8bit/ui/plots/simple/simplegraph.h"
#include "pid.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonGo_clicked();

    void on_doubleSpinBoxP_valueChanged(double arg1);

    void on_doubleSpinBoxI_valueChanged(double arg1);

    void on_doubleSpinBoxD_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    PID *pid;
    void oneSet(double start, double target);
    void go();
    int x=0;
    SimpleGraph *targetPlot, *currentValPlot, *deltaPlot;
};

#endif // MAINWINDOW_H
