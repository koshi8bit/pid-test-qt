#include "abstractplot.h"
#include "ui_abstractplot.h"

AbstractPlot::AbstractPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractPlot)
{
    ui->setupUi(this);
    ui->widgetToolTip->setVisible(false);
    configureLegend();

    _qcp = ui->plot;
    connect(qcp(), &QCustomPlot::axisClick, this, &AbstractPlot::axisClick);
    connect(qcp(), &QCustomPlot::axisDoubleClick, this, &AbstractPlot::axisDoubleClick);

    ui->splitter->setStretchFactor(0, 5);
    ui->splitter->setStretchFactor(1, 1);

    //ui->splitter->widget(1)->setMinimumWidth(100);
    ui->splitter->setCollapsible(0, false);
    connect(ui->splitter, &QSplitter::splitterMoved,
            this, &AbstractPlot::_splitterMoved);

    setButtonsVisible(false, false);

}

AbstractPlot::~AbstractPlot()
{
    delete ui;
}

void AbstractPlot::axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(part)
    if (event->button() == Qt::MouseButton::RightButton)
    {
        autoScaleAxis(axis);
        qcp()->replot();
    }
}

void AbstractPlot::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    abstractAxisDoubleClick(axis, part, event);
}

void AbstractPlot::autoScaleAxis(QCPAxis *axis)
{
    axis->rescale(true);
    auto delta = (axis->range().upper - axis->range().lower)*0.05; // 5%
    axis->setRange(axis->range().lower - delta, axis->range().upper + delta);
}

void AbstractPlot::setButtonsVisible(bool visible, bool options)
{
    ui->pushButtonHelp->setVisible(visible);
    ui->pushButtonPrintScreen->setVisible(visible);
    ui->pushButtonPrintScreenCopy->setVisible(visible);
    ui->pushButtonPrintScreenPaint->setVisible(visible);

    if (options)
        ui->pushButtonOptions->setVisible(visible);
}

void AbstractPlot::addAbstractGraph(AbstractGraph *graph)
{
    _graphs.append(graph);
    _legendLayout->insertWidget(_legendLayout->count()-1, graph->legendItem());
}

void AbstractPlot::setLegendVisible(bool visible)
{
    ui->scrollAreaLegend->setVisible(visible);
}

void AbstractPlot::setSplitterWidth(int widthL, int widthR, AbstractPlot *senderWidget)
{
    if (senderWidget == this) return;

    _setSplitterWidth(widthL, widthR);
}

void AbstractPlot::setSplitterWidth(int widthR)
{
    QList<int> sizes = ui->splitter->sizes();
    auto widthL = sizes[0] + sizes[1] - widthR;
    setSplitterWidth(widthL, widthR);

}

void AbstractPlot::setSplitterWidth(int widthL, int widthR)
{
    _setSplitterWidth(widthL, widthR);
    emit splitterWidthChanged(widthL, widthR);
}


QVector<AbstractGraph *> AbstractPlot::graphs()
{
    return _graphs;
}



void AbstractPlot::configureLegend()
{
    _legendLayout = new QVBoxLayout(ui->scrollAreaLegend->widget());

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    _legendLayout->addItem(spacer);
}

void AbstractPlot::configurePlotBackground(bool excelStyle)
{
    configurePlotBackgroundAxis(qcp()->xAxis, excelStyle);
    configurePlotBackgroundAxis(qcp()->yAxis, excelStyle);
    configurePlotBackgroundAxis(qcp()->yAxis2, excelStyle);


    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    qcp()->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(60, 60, 60));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    qcp()->axisRect()->setBackground(axisRectGradient);
}

void AbstractPlot::configurePlotBackgroundAxis(QCPAxis *axis, bool excelStyle, QColor color)
{
    axis->setLabelColor(color);
    axis->setBasePen(QPen(color, 1));
    axis->setSubTickPen(QPen(color, 1));
    axis->setTickLabelColor(color);
    axis->setTickPen(QPen(color, 1));
    if (excelStyle)
    {
        axis->grid()->setPen(QPen(QColor(80, 80, 80), 1, Qt::SolidLine));
    }
    else
    {
        axis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
        axis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
        axis->grid()->setSubGridVisible(true);
    }
    axis->grid()->setZeroLinePen(Qt::NoPen);
}

void AbstractPlot::abstractAxisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(part)
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        auto plot = static_cast<QCustomPlot *>(sender());
        AxisValueConfig ac(axis, this);
        //ac.setModal(true);
        ac.exec();
        plot->replot();
    }
}

QCustomPlot *AbstractPlot::qcp()
{
    return _qcp;
}

void AbstractPlot::on_pushButtonOptions_toggled(bool checked)
{
    setButtonsVisible(checked, false);
}

void AbstractPlot::on_pushButtonPrintScreenCopy_clicked()
{
    setButtonsVisible(false, true);
    PrintScreener::copy(this);
    ui->pushButtonOptions->setVisible(true);
    ui->pushButtonOptions->setChecked(false);

}

void AbstractPlot::on_pushButtonPrintScreenPaint_clicked()
{
    setButtonsVisible(false, true);
    auto path = PrintScreener::save(this, "", true);
    //setButtonsVisible(true, true);
    ui->pushButtonOptions->setVisible(true);
    ui->pushButtonOptions->setChecked(false);

    if (path.isEmpty())
        return;

    EasyLiving::exec("mspaint.exe", { path.replace("/", "\\") });
}

void AbstractPlot::_splitterMoved(int pos, int index)
{
    Q_UNUSED(pos)
    Q_UNUSED(index)
    QList<int> currentSizes = ui->splitter->sizes();
    qDebug() << Q_FUNC_INFO << currentSizes;
    emit splitterWidthChanged(currentSizes[0], currentSizes[1]);
}

void AbstractPlot::on_pushButtonPrintScreen_clicked()
{
    setButtonsVisible(false, true);
    PrintScreener::save(this);
    ui->pushButtonOptions->setVisible(true);
    ui->pushButtonOptions->setChecked(false);

}

void AbstractPlot::on_pushButtonHelp_clicked()
{
    setButtonsVisible(false, false);
    ui->pushButtonOptions->setChecked(false);
    QMessageBox::about(this, "Help", ui->widgetToolTip->toolTip());
}


//void AbstractPlot::configureAxis(bool yAxis2, const QString &label, const QString &postfix, double min, double max, int precision, QCPAxis::ScaleType scaleType)
//{
//    configureAxis(yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
//                  label,
//                  postfix,
//                  min,
//                  max,
//                  precision,
//                  scaleType);
//}

//void AbstractPlot::configureAxis(QCPAxis *axis, ChannelDouble *channel, double min, double max)
//{
//    configureAxis(axis,
//                  channel->plotName(),
//                  channel->postfix(),
//                  min, max,
//                  channel->precision(),
//                  channel->scientificNotation() ? QCPAxis::ScaleType::stLogarithmic : QCPAxis::ScaleType::stLinear);
//}

void AbstractPlot::configureAxis(QCPAxis *axis, const QString &label, const QString &postfix, double min, double max, int precision, QCPAxis::ScaleType scaleType, QColor color)
{
    if (postfix.isEmpty())
    {
        axis->setLabel(label);
    }
    else
    {
        axis->setLabel(QString("%1 [%2]").arg(label).arg(postfix));
    }
    axis->setVisible(true);
    axis->setRange(min, max);
    setAxisType(axis, scaleType);
    axis->setNumberPrecision(precision);
    configurePlotBackgroundAxis(axis, false, color);
    //axis->setLabelPadding(20);
    qcp()->replot();

}

void AbstractPlot::setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType)
{
    //TODO DRY see AxisValueConfig, may be make static method from there
    if (scaleType == QCPAxis::ScaleType::stLinear)
    {
        axis->setScaleType(QCPAxis::stLinear);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTicker);
        axis->setTicker(ticker);
        axis->setNumberFormat("f");
        axis->setNumberPrecision(1);
    }

    if (scaleType == QCPAxis::ScaleType::stLogarithmic)
    {
        axis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        axis->setTicker(logTicker);
        axis->setNumberFormat("eb");
        axis->setNumberPrecision(0);
    }
}

void AbstractPlot::_setSplitterWidth(int widthL, int widthR)
{
//    auto size = ui->splitter->widget(1)->geometry();
//    ui->splitter->widget(1)->resize(widthL, size.height());

    QList<int> currentSizes;
    currentSizes.append(widthL);
    currentSizes.append(widthR);
    ui->splitter->setSizes(currentSizes);
}
