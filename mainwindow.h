
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
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

private:
    Ui::MainWindow *ui;
    PID *pid;
    void oneSet(double start, double end);
    int x=0;
    SimplePlot *targetPlot, *currentValPlot, *deltaPlot;
};

#endif // MAINWINDOW_H
