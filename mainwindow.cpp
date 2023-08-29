
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pid = new PID(0.1, -100, 100,
                  ui->doubleSpinBoxP->value(),
                  ui->doubleSpinBoxI->value(),
                  ui->doubleSpinBoxD->value());



    targetPlot = ui->plot->addGraph("target", SimpleGraph::line);
    currentValPlot = ui->plot->addGraph("current val", SimpleGraph::line);
    deltaPlot = ui->plot->addGraph("delta", SimpleGraph::line);

    go();

    oneSet(ui->doubleSpinBoxEnd1->value(),
           ui->doubleSpinBoxEnd2->value());

    ui->plot->autoScaleAllAxis();
    //ui->plot->setSplitterWidth(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonGo_clicked()
{
    go();
}

void MainWindow::oneSet(double start, double target)
{
    auto currVal = start;
    auto n = 100;
    for (int i = 0; i < n; i++) {
        double delta = pid->calc(target, currVal);
        currVal += delta;

        targetPlot->addData(i+x, target);
        currentValPlot->addData(i+x, currVal);
        deltaPlot->addData(i+x, delta);
    }
    x += n;
}

void MainWindow::go()
{
    oneSet(ui->doubleSpinBoxStart->value(),
           ui->doubleSpinBoxEnd1->value());
    ui->plot->autoScaleAllAxis();
}


void MainWindow::on_doubleSpinBoxP_valueChanged(double arg1)
{
    pid->setP(arg1);
}


void MainWindow::on_doubleSpinBoxI_valueChanged(double arg1)
{
    pid->setI(arg1);
}


void MainWindow::on_doubleSpinBoxD_valueChanged(double arg1)
{
    pid->setD(arg1);
}

