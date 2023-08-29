
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pid = new PID(0.1, -100, 100, 0.1, 0.5, 0.1);
    targetPlot = ui->plot->addGraph("target");
    currentValPlot = ui->plot->addGraph("current val");
    deltaPlot = ui->plot->addGraph("delta");

    double currentVal = 20;
    double target = 0;

    target = 10;

    for (int i = 100; i < 200; i++) {
        double delta = pid->calc(target, currentVal);
        //printf("val:% 7.3f inc:% 7.3f\n", val, inc);
        qDebug() << "val" << currentVal << "delta" << delta;
        currentVal += delta;

        targetPlot->addData(i, target);
        currentValPlot->addData(i, currentVal);
        deltaPlot->addData(i, delta);

    }
    qDebug() << "jj";
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButtonGo_clicked()
{

}

void MainWindow::oneSet(double start, double end)
{
    for (int i = 0; i < 100; i++) {
        double delta = pid->calc(start, start);
        //printf("val:% 7.3f inc:% 7.3f\n", val, inc);
        //qDebug() << "val" << currentVal << "delta" << delta;
        start += delta;

        targetPlot->addData(i, start);
        currentValPlot->addData(i, start);
        deltaPlot->addData(i, delta);
    }

}

