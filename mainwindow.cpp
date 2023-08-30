
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->doubleSpinBoxCursorP->setValue(0.1);
    ui->doubleSpinBoxCursorP->setDecimals(4);
    ui->doubleSpinBoxCursorP->setPrefix("P ");
    ui->doubleSpinBoxCursorP->setMinMax(-100, 100);
    connect(ui->doubleSpinBoxCursorP, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        //pid->setP(val);
        Q_UNUSED(val)
        go();
    });

    ui->doubleSpinBoxCursorI->setValue(0.5);
    ui->doubleSpinBoxCursorI->setDecimals(4);
    ui->doubleSpinBoxCursorI->setPrefix("I ");
    ui->doubleSpinBoxCursorI->setMinMax(-100, 100);
    connect(ui->doubleSpinBoxCursorI, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        //pid->setI(val);
        Q_UNUSED(val)
        go();
    });

    ui->doubleSpinBoxCursorD->setValue(0.01);
    ui->doubleSpinBoxCursorD->setDecimals(4);
    ui->doubleSpinBoxCursorD->setPrefix("D ");
    ui->doubleSpinBoxCursorD->setMinMax(-100, 100);
    connect(ui->doubleSpinBoxCursorD, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        //pid->setD(val);
        Q_UNUSED(val)
        go();
    });

    ui->doubleSpinBoxCursorStart->setValue(20);
    ui->doubleSpinBoxCursorStart->setPrefix("start: ");
    ui->doubleSpinBoxCursorStart->setMinMax(-100, 100);
    connect(ui->doubleSpinBoxCursorStart, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        Q_UNUSED(val)
        go();
    });

    ui->doubleSpinBoxCursorTarget->setValue(0);
    ui->doubleSpinBoxCursorTarget->setPrefix("target: ");
    ui->doubleSpinBoxCursorTarget->setMinMax(-100, 100);
    connect(ui->doubleSpinBoxCursorTarget, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        Q_UNUSED(val)
        go();
    });

    pid = new PID(0.1, -100, 100,
                  ui->doubleSpinBoxCursorP->value(),
                  ui->doubleSpinBoxCursorI->value(),
                  ui->doubleSpinBoxCursorD->value());


    targetPlot = ui->plot->addGraph("target", SimpleGraph::line);
    currentValPlot = ui->plot->addGraph("current val", SimpleGraph::line);
    deltaPlot = ui->plot->addGraph("delta", SimpleGraph::line);
    deltaPlot->setVisible(false);

    go();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonGo_clicked()
{
    go();
}

void MainWindow::go()
{
    auto currVal = ui->doubleSpinBoxCursorStart->value();
    auto setpoint = ui->doubleSpinBoxCursorTarget->value();
    auto n = 100;
    auto max = currVal;
    auto min = currVal;

    pid->setP(ui->doubleSpinBoxCursorP->value());
    pid->setI(ui->doubleSpinBoxCursorI->value());
    pid->setD(ui->doubleSpinBoxCursorD->value());

    for (int i = 0; i < n; i++) {
        double delta = pid->calc(currVal, setpoint);
        currVal += delta;
        if (currVal > max) {
            max = currVal;
        }

        if (currVal < min) {
            min = currVal;
        }

        targetPlot->addData(i+x, setpoint);
        currentValPlot->addData(i+x, currVal);
        deltaPlot->addData(i+x, delta);
    }
    x += n;

    if (ui->checkBoxOnlyLast->isChecked()) {
        ui->plot->qcp()->xAxis->setRange(x-n, x);
        ui->plot->qcp()->yAxis->setRange(min*1.05, max*1.05);
    }

    if (ui->checkBoxAutoSwap->isChecked()) {
        on_pushButtonSwap_clicked();
    }

    ui->plot->qcp()->replot();
}

void MainWindow::on_pushButtonReset_clicked()
{
    pid->reset();
}

void MainWindow::on_pushButtonSwap_clicked()
{
    auto tmp = ui->doubleSpinBoxCursorStart->value();
    ui->doubleSpinBoxCursorStart->setValue(ui->doubleSpinBoxCursorTarget->value());
    ui->doubleSpinBoxCursorTarget->setValue(tmp);
}

