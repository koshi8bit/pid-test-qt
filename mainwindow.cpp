
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->doubleSpinBoxCursorP->setMinMax(-100, 100);
    ui->doubleSpinBoxCursorP->setValue(0.1);
    ui->doubleSpinBoxCursorP->setDecimals(4);
    ui->doubleSpinBoxCursorP->setPrefix("P ");
    connect(ui->doubleSpinBoxCursorP, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        //pid->setP(val);
        Q_UNUSED(val)
        go();
    });

    ui->doubleSpinBoxCursorI->setMinMax(-100, 100);
    ui->doubleSpinBoxCursorI->setValue(0.5);
    ui->doubleSpinBoxCursorI->setDecimals(4);
    ui->doubleSpinBoxCursorI->setPrefix("I ");
    connect(ui->doubleSpinBoxCursorI, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        //pid->setI(val);
        Q_UNUSED(val)
        go();
    });

    ui->doubleSpinBoxCursorD->setMinMax(-100, 100);
    ui->doubleSpinBoxCursorD->setValue(0.01);
    ui->doubleSpinBoxCursorD->setDecimals(4);
    ui->doubleSpinBoxCursorD->setPrefix("D ");
    connect(ui->doubleSpinBoxCursorD, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        //pid->setD(val);
        Q_UNUSED(val)
        go();
    });

    ///

    ui->doubleSpinBoxCursorArcGet->setMinMax(0, 200);
    ui->doubleSpinBoxCursorArcGet->setValue(80);
    ui->doubleSpinBoxCursorArcGet->setPrefix("Дуга измер.: ");
    connect(ui->doubleSpinBoxCursorArcGet, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        Q_UNUSED(val)
        go();
    });

    ui->doubleSpinBoxCursorArcTarget->setMinMax(0, 200);
    ui->doubleSpinBoxCursorArcTarget->setValue(100);
    ui->doubleSpinBoxCursorArcTarget->setPrefix("Дуга цель: ");
    connect(ui->doubleSpinBoxCursorArcTarget, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        Q_UNUSED(val)
        go();
    });

    //

    ui->doubleSpinBoxCursorFilamentStart->setMinMax(0, 400);
    ui->doubleSpinBoxCursorFilamentStart->setValue(200);
    ui->doubleSpinBoxCursorFilamentStart->setPrefix("Накал начальное: ");
    connect(ui->doubleSpinBoxCursorFilamentStart, &DoubleSpinBoxCursor::valueConfirmed, [this](double val) {
        Q_UNUSED(val)
        go();
    });

    //

    pid = new PID(0.1, -100, 100,
                  ui->doubleSpinBoxCursorP->value(),
                  ui->doubleSpinBoxCursorI->value(),
                  ui->doubleSpinBoxCursorD->value());


    arcGetPlot = ui->plot->addGraph("Дуга измер.", SimpleGraph::line);
    arcTargetPlot = ui->plot->addGraph("Дуга цель", SimpleGraph::line);
    arcDeltaPlot = ui->plot->addGraph("Дуга delta (PID input)", SimpleGraph::line);
    arcDeltaPlot->setVisible(false);
    filamentSetPlot = ui->plot->addGraph("Накал уст.", SimpleGraph::line);
    filamentDeltaPlot = ui->plot->addGraph("Накал delta", SimpleGraph::line);


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
    auto arcDelta = ui->doubleSpinBoxCursorArcTarget->value() -
                    ui->doubleSpinBoxCursorArcGet->value();
    auto filamentSet = ui->doubleSpinBoxCursorFilamentStart->value();
    auto n = 100;
//    auto max = currVal;
//    auto min = currVal;

    pid->setP(ui->doubleSpinBoxCursorP->value());
    pid->setI(ui->doubleSpinBoxCursorI->value());
    pid->setD(ui->doubleSpinBoxCursorD->value());

    for (int i = 0; i < n; i++) {
        double filamentDelta = pid->calc(ui->doubleSpinBoxCursorArcGet->value(),
                                         ui->doubleSpinBoxCursorArcTarget->value());
        filamentSet += filamentDelta;
//        if (deltaArc > max) {
//            max = currVal;
//        }

//        if (currVal < min) {
//            min = currVal;
//        }

        arcGetPlot->addData(i+x, ui->doubleSpinBoxCursorArcGet->value());
        arcTargetPlot->addData(i+x, ui->doubleSpinBoxCursorArcTarget->value());
        arcDeltaPlot->addData(i+x, arcDelta);
        filamentSetPlot->addData(i+x, filamentSet);
        filamentDeltaPlot->addData(i+x, filamentDelta);
    }
    x += n;

//    if (ui->checkBoxOnlyLast->isChecked()) {
//        ui->plot->qcp()->xAxis->setRange(x-n, x);
//        ui->plot->qcp()->yAxis->setRange(min*1.05, max*1.05);
//    }



    ui->plot->qcp()->replot();
}

void MainWindow::on_pushButtonReset_clicked()
{
    pid->reset();
}

