#include "realtimeplot.h"

RealTimePlot::RealTimePlot(QWidget *parent)
    :AbstractPlot(parent)
{
    labelTime = new QLabel(this);
    labelTime->setText(timeLabel);
    _legendLayout->insertWidget(0, labelTime);

    //connect(qcp(), &QCustomPlot::mouseMove, this, &RTPlotWithLegend::mouseMove);
    connect(qcp(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(qcp(), &QCustomPlot::mousePress, this, &RealTimePlot::mousePress);
    connect(qcp(), &QCustomPlot::mouseDoubleClick, this, &RealTimePlot::mouseDoubleClick);
    connect(qcp(), &QCustomPlot::mouseWheel, this, &RealTimePlot::mouseWheel);
    //connect(qcp(), SIGNAL(mouseWheel(QMouseEvent*)), this, SLOT(mouseWheel(QMouseEvent*)));

    connect(qcp(), &QCustomPlot::beforeReplot, this, &RealTimePlot::beforeReplot);
    connect(qcp()->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(setTimeAxisRange(QCPRange)));

    configureStatusLabel();
    _configurePlot();
    _setCursor2Visible(false);
    updateStatusLabelFlag = true;

    timerZoom.setInterval(100);
    timerZoom.setSingleShot(true);
    connect(&timerZoom, &QTimer::timeout, [this]() {
//        auto a = ui->splitter->sizes();
        configureAxesZoomAndDrag(!realTime());
//        qDebug() << "timerZoom";
    });
    qcp()->replot();
}

RealTimePlot::~RealTimePlot()
{
    //FIXME deleteLater
    //FIXME "FTH: (8440): *** Fault tolerant heap.."
    //delete ui;
}

void RealTimePlot::abstractAxisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(part)
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        auto plot = static_cast<QCustomPlot *>(sender());
        if (qcp()->xAxis == axis)
        {
            AxisTimeConfig ac(axis, this);
            ac.setModal(true);
            ac.exec();
        }
        else
        {
            AxisValueConfig ac(axis, this);
            ac.setModal(true);
            ac.exec();
        }

        plot->replot();
    }
}

bool RealTimePlot::realTime() const
{
    return _realTime;
}

void RealTimePlot::configureStatusLabel()
{
    statusLabel = new QCPItemText(qcp());
    statusLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    statusLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    statusLabel->position->setCoords(1, 0.95); // lower right corner of axis rect

    statusLabel->setTextAlignment(Qt::AlignLeft);
    statusLabel->setFont(QFont(font().family(), 10));
    statusLabel->setPadding(QMargins(2, 0, 2, 0));
    statusLabel->setBrush(QColor("#C0C0C0"));
    statusLabel->setVisible(false);
}

void RealTimePlot::updateStatusLabel()
{
    if (updateStatusLabelFlag)
    {
        QString text;
        if (realTime()) text.append("R ");
        if (!moveLineRealTime()) text.append("C1 ");
        if (cursor2Visible()) text.append("C2 ");
        statusLabel->setText(text.trimmed());
        statusLabel->setVisible(!text.isEmpty());
    }
}



void RealTimePlot::_configurePlot()
{
    //WARNING dublicate configureAxesZoomAndDrag??
    qcp()->setInteraction(QCP::iRangeZoom, true);
    qcp()->setInteraction(QCP::iRangeDrag, true);

    setRealTime(true);

    //WARNING dublicate exec in setRealTime
    //configureAxesZoomAndDrag(false);

    configurePlotBackground(false);

    configurePlotTimeAxis();
    configurePlotLine();
    setMoveLineRealTime(true);
    qcp()->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    qcp()->xAxis->setRangeUpper(RealTimePlot::currentDateTime());
    setTimeAxisRange(60);

    // { Tests
    //qcp()->setNoAntialiasingOnDrag(true);
    //qcp()->setPlottingHint(QCP::phFastPolylines,true); // ?tima45 line from ethernet

    // } Tests


}


void RealTimePlot::_setRealTime(bool newValue)
{
    _realTime = newValue;
    configureAxesZoomAndDrag(!newValue);
    //configureAxesZoomAndDrag(true);
    updateStatusLabel();
}

void RealTimePlot::setRealTime(bool newValue)
{
    _setRealTime(newValue);
    emit realTimeChanged(newValue);
}

void RealTimePlot::setCursor2Visible(bool newValue)
{
    _setCursor2Visible(newValue);
    emit cursor2VisibleValueChanged(newValue);
}

void RealTimePlot::setCursor2Key(double key)
{
    _setCursor2Key(key);
    emit cursor2KeyChanged(key);
}

void RealTimePlot::setTimeAxisRange(const QCPRange &newValue)
{
    _setTimeAxisRange(newValue);
    emit timeAxisRangeChanged(newValue);
}

RealTimeGraph *RealTimePlot::graphCast(AbstractGraph *graph)
{
    return dynamic_cast<RealTimeGraph *>(graph);
}

bool RealTimePlot::dayStyle() const
{
    return _dayStyle;
}

QCPItemLine *RealTimePlot::cursor2() const
{
    return _cursor2;
}

bool RealTimePlot::moveLineRealTime() const
{
    return _moveLineRealTime;
}

void RealTimePlot::moveTimeAxisRealTime()
{
//    auto range = qcp()->xAxis->range();
//    auto delta = range.upper - range.lower;
    if (!this->isVisible())
        return;

    if (realTime())
    {
        auto cdt = currentDateTime();

        qcp()->xAxis->setRange(cdt - timeAxisOldRange, cdt);
    }
    qcp()->replot();
}

void RealTimePlot::setTimeAxisRange(int newRangeMSEC)
{
    qcp()->xAxis->setRangeLower(qcp()->xAxis->range().upper - newRangeMSEC);
    updateTimeAxisLabel();
}

void RealTimePlot::setTimeLabelVisible(bool newValue)
{
    labelTime->setVisible(newValue);
}

void RealTimePlot::setMarginGroup(QCPMarginGroup *mg)
{
    qcp()->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, mg);
}

double RealTimePlot::currentDateTime()
{
    return dateTimeToKey(QDateTime::currentDateTime());
}

double RealTimePlot::dateTimeToKey(QDateTime dt)
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    return dt.toTime_t() + static_cast<double>(dt.time().msec())/1000;
#else
    return dt.toSecsSinceEpoch() + static_cast<double>(dt.time().msec())/1000;
#endif

}

QDateTime RealTimePlot::keyToDateTime(double key)
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    return QDateTime::fromTime_t(static_cast<uint>(key));
#else
    return QDateTime::fromSecsSinceEpoch(static_cast<uint>(key));
#endif

}

RealTimeGraph *RealTimePlot::addGraph(const QString &label, const QString &postfix, int precision, bool scientificNotation)
{
    return addGraph(qcp()->yAxis, label, postfix, precision, scientificNotation);
}

RealTimeGraph *RealTimePlot::addGraph(QCPAxis *axis, const QString &label, const QString &postfix, int precision, bool scientificNotation)
{
    auto graph = new RealTimeGraph( label,
                            postfix,
                            colorSetter.getColor(),
                            qcp(),
                            axis,
                            precision,
                            scientificNotation);

    addAbstractGraph(graph);
    return graph;
}

ErrorYGraph *RealTimePlot::addGraphErrorY(const QString &label, const QString &postfix, bool yAxis2, int precision, bool scientificNotation)
{
    auto graph = new ErrorYGraph(label,
                                 postfix,
                                 colorSetter.getColor(),
                                 qcp(),
                                 yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                                 precision,
                                 scientificNotation);
    addAbstractGraph(graph);
    return graph;
}

ErrorXYGraph *RealTimePlot::addGraphErrorXY(const QString &label, const QString &postfix, bool yAxis2, int precision, bool scientificNotation)
{
    auto graph = new ErrorXYGraph(label,
                                 postfix,
                                 colorSetter.getColor(),
                                 qcp(),
                                 yAxis2 ? qcp()->yAxis2 : qcp()->yAxis,
                                 precision,
                                 scientificNotation);
    addAbstractGraph(graph);
    return graph;
}

void RealTimePlot::removeGraphs()
{
    foreach(auto g , graphs())
    {
        g->deleteLater();
    }
    _graphs.clear();
    colorSetter.resetColors();
}

void RealTimePlot::removeGraph(RealTimeGraph *graph)
{
    _graphs.removeOne(graph);
    _legendLayout->removeWidget(graph->legendItem());
    graph->deleteLater();
}

void RealTimePlot::removeAxes()
{
    auto axis = QList<QCPAxis*>();
    axis.append(qcp()->axisRect()->axes(QCPAxis::atLeft));
    axis.append(qcp()->axisRect()->axes(QCPAxis::atRight));

    foreach(auto a, axis) {
        if (a == qcp()->xAxis)
            continue;
        if (a == qcp()->yAxis)
            continue;

        qcp()->axisRect()->removeAxis(a);
    }

}




void RealTimePlot::_setCursor2Visible(bool newValue)
{
    _cursor2->setVisible(newValue);
    //foreach (auto graphElement, foo<RealTimeGraph*>())
    foreach (auto graphElement, graphs())
    {
        auto tmp = graphCast(graphElement);
        if (tmp)
            tmp->setCursor2Visible(newValue);
    }

    if (labelTime->isVisible())
        labelTime->setText(formatLabelTime(_cursor->start->key()));

    updateStatusLabel();
}

void RealTimePlot::_setCursor2Key(double key)
{
    foreach (auto graphElement, graphs())
    {
        auto tmp = graphCast(graphElement);
        if (tmp)
            tmp->moveCursor2(_cursor->start->key());
    }

    _cursor2->start->setCoords(key, _cursor->start->coords().y());
    _cursor2->end->setCoords(key, _cursor->end->coords().y());
    _setCursor2Visible(true);
    qcp()->replot();
    updateStatusLabel();
}

double RealTimePlot::getYAxisUpper()
{
    return qMax(qcp()->yAxis->range().upper,
                qcp()->yAxis2->range().upper);
}

double RealTimePlot::getYAxisLower()
{
    return qMin(qcp()->yAxis->range().lower,
                qcp()->yAxis2->range().lower);

}

bool RealTimePlot::cursor2Visible()
{
    return _cursor2->visible();
}


void RealTimePlot::setCursor2Visible(bool newValue, RealTimePlot *senderWidget)
{
    if (senderWidget == this) { return; }

    _setCursor2Visible(newValue);
}

void RealTimePlot::setCursor2Key(double key, RealTimePlot *senderWidget)
{
    if (senderWidget == this) { return; }

    _setCursor2Key(key);
}

void RealTimePlot::setMoveLineRealTime(bool newValue, RealTimePlot *senderWidget)
{
    if (senderWidget == this) { return; }

    _setMoveLineRealTime(newValue);
}

void RealTimePlot::setRealTime(bool newValue, RealTimePlot *senderWidget)
{
    if (senderWidget == this) { return; }

    _setRealTime(newValue);
}

void RealTimePlot::setCursorKey(double key, RealTimePlot *senderWidget)
{
    if (senderWidget == this) { return; }

    _setCursorKey(key);
}

void RealTimePlot::setTimeAxisRange(const QCPRange &newRange, RealTimePlot *senderWidget)
{
    if (senderWidget == this) { return; }

    _setTimeAxisRange(newRange);
}

void RealTimePlot::configureTimerReplot(int intervalMSEC)
{
    timerReplot = new QTimer(this);
    timerReplot->setInterval(intervalMSEC);
    connect(timerReplot, &QTimer::timeout, this, &RealTimePlot::moveTimeAxisRealTime);
    timerReplot->start();
    configureAxesZoomAndDrag(false);

}

void RealTimePlot::setIntervalTimerReplot(int intervalMSEC)
{
    timerReplot->setInterval(intervalMSEC);
}


void RealTimePlot::_setMoveLineRealTime(bool newValue)
{
    _moveLineRealTime = newValue;
    updateStatusLabel();
}

void RealTimePlot::setMoveLineRealTime(bool newValue)
{
    _setMoveLineRealTime(newValue);
    emit moveLineRealTimeChanged(newValue);
}


void RealTimePlot::configureAxesZoomAndDrag(bool configureXAxises)
{
//    auto axis = QList<QCPAxis*>()
//            << qcp()->yAxis
//            << qcp()->yAxis2;
    auto axis = QList<QCPAxis*>();
    axis.append(qcp()->axisRect()->axes(QCPAxis::atLeft));
    axis.append(qcp()->axisRect()->axes(QCPAxis::atRight));


    if (configureXAxises)
        axis << qcp()->xAxis;
    qcp()->axisRect()->setRangeZoomAxes(axis);
    qcp()->axisRect()->setRangeDragAxes(axis);

//    auto zoom = QList<QCPAxis*>()
//            << qcp()->xAxis;

//    if (configureYAxises)
//    {
//        zoom << qcp()->yAxis
//             << qcp()->yAxis2;
//    }

//    auto drag = QList<QCPAxis*>()
//            << qcp()->yAxis
//            << qcp()->yAxis2
//            << qcp()->xAxis;

//    qcp()->axisRect()->setRangeZoomAxes(zoom);
//    qcp()->axisRect()->setRangeDragAxes(drag);


}




void RealTimePlot::configurePlotTimeAxis()
{
    qcp()->xAxis->setLabel(timeLabel);
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss");
    qcp()->xAxis->setTicker(dateTicker);
}

void RealTimePlot::configurePlotLine()
{
    configurePlotLine(&_cursor);
    configurePlotLine(&_cursor2);
}

void RealTimePlot::configurePlotLine(QCPItemLine **line)
{
    (*line) = new QCPItemLine(qcp());
    auto pen = QPen();
    pen.setColor("#C0C0C0");
    pen.setStyle(Qt::PenStyle::DashLine);
    (*line)->setPen(pen);

    (*line)->start->setCoords(qcp()->xAxis->range().upper, qcp()->yAxis->range().upper);
    (*line)->end->setCoords(qcp()->xAxis->range().upper, qcp()->yAxis->range().lower);
}

void RealTimePlot::updateTimeAxisLabel()
{
    //auto delta = qcp()->xAxis->range().upper - qcp()->xAxis->range().lower;
    auto begin = keyToDateTime(qcp()->xAxis->range().upper);
    auto end = keyToDateTime(qcp()->xAxis->range().lower);
    auto delta = EasyLiving::dateTimeDelta(begin, end, false);
    qcp()->xAxis->setLabel(QString("%1 [%2]").arg(timeLabel).arg(delta));

    //  deleteLater
//    if (dayStyle())
//    {
//        auto dt = new QDateTime(QDate(0, 0, 0), QTime(0, 0, 0));

//    }
//    else
//    {
//        auto t = QTime(0, 0, 0).addSecs(static_cast<int>(delta));
//        qcp()->xAxis->setLabel(QString("%1 [%2]").arg(timeLabel).arg(t.toString(EasyLiving::formatTimeUi(false))));
//    }

}



void RealTimePlot::setDayStyle(bool dayStyle, bool showTime)
{
    _dayStyle = dayStyle;
    if (dayStyle)
    {
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
        auto format = EasyLiving::formatDateUi();
        if (showTime)
            format.append("\n"+EasyLiving::formatTimeUi());
        dateTicker->setDateTimeFormat(format);
        qcp()->xAxis->setTicker(dateTicker);

        setRealTime(false);

        foreach(auto g, graphs())
        {
            auto tmp = graphCast(g);
            if (tmp)
                tmp->graph()->setLineStyle(QCPGraph::lsLine);
//            g->graph()->setLineStyle(QCPGraph::lsNone);
//            g->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        }
    }
}

void RealTimePlot::mouseMove(QMouseEvent *event)
{
//    if (isInAxisRect(event->pos()))
//    {

//    }
    if (realTime() && moveLineRealTime()) return;

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    auto time = qcp()->xAxis->pixelToCoord(event->x());
#else
    auto time = qcp()->xAxis->pixelToCoord(event->position().x());
#endif

    setCursorKey(time);
}

void RealTimePlot::mousePress(QMouseEvent *event)
{
    //configureAxesZoomAndDrag(isInAxisRect(event->pos()));
    //qDebug() << isInAxisRect(event->pos());
    if (isInAxisRect(event->pos()))
    {
        if (event->button() == Qt::MouseButton::RightButton)
        {
            setMoveLineRealTime(!moveLineRealTime());
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            auto time = qcp()->xAxis->pixelToCoord(event->x());
#else
            auto time = qcp()->xAxis->pixelToCoord(event->position().x());
#endif
            setCursorKey(time);
        }

        if (event->button() == Qt::MouseButton::MiddleButton)
        {
            if (!cursor2Visible())
            {
                setCursor2Key(_cursor->start->key());
            }
            else
            {
                setCursor2Visible(false);
            }


            foreach (auto graphElement, graphs())
            {
                auto tmp = graphCast(graphElement);
                if (tmp)
                    tmp->updateValue();
            }


        }

    }
}

void RealTimePlot::mouseDoubleClick(QMouseEvent *event)
{
    if (isInAxisRect(event->pos()))
    {
        if (event->button() == Qt::MouseButton::LeftButton)
        {
            auto newValue = !realTime();
            setRealTime(newValue);

            setMoveLineRealTime(newValue);

        }
    }
}

void RealTimePlot::mouseWheel(QWheelEvent *event)
{
    Q_UNUSED(event)
    //qDebug() << "mouseWheel";
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    configureAxesZoomAndDrag(!isInAxisRect(event->pos()));
#else
    configureAxesZoomAndDrag(!isInAxisRect(event->position().toPoint()));
#endif
    //qDebug() << isInAxisRect(event->pos()) << realTime();
    timerZoom.start();
    //configureAxesZoomAndDrag(isInAxisRect(event->pos()));
    //qDebug() << isInAxisRect(event->pos());
    moveTimeAxisRealTime();
}

void RealTimePlot::beforeReplot()
{
    //WARNING update values without dependence of _line position
    //next fix here
    if (moveLineRealTime())
    {
        //TODO set to 1970 and don't move
        setCursorKey(currentDateTime());
    }
}

void RealTimePlot::_setTimeAxisRange(const QCPRange &newRange)
{
    qcp()->xAxis->setRange(newRange);
    auto delta = newRange.upper - newRange.lower;
    if (!EasyLiving::isEqualDouble(timeAxisOldRange, delta))
    {
        timeAxisOldRange = delta;
        updateTimeAxisLabel();
    }
    updateStatusLabel();
}


void RealTimePlot::_setCursorKey(double time)
{
    //BUG ?is this mouse move or regular move by timer?
    if (labelTime->isVisible())
        labelTime->setText(formatLabelTime(time));

    foreach (auto graphElement, graphs())
    {
        auto tmp = graphCast(graphElement);
        if (tmp)
            tmp->moveCursor(time);
    }

    //    auto lower = getYAxisLower();
    //    auto upper = getYAxisUpper();
    auto lower = -9999999999;
    auto upper = +9999999999;


    _cursor->start->setCoords(time, lower);
    _cursor->end->setCoords(time, upper);

    //NOTE check cpu usage too big
    //NOTE inf loop
//    if(!realTime())
//    {
//        qcp()->replot();
//    }
}

void RealTimePlot::setCursorKey(double time)
{
    _setCursorKey(time);
    emit cursorKeyChanged(time);

}


QString RealTimePlot::formatLabelTime(double key)
{
    //TODO show MSEC ?formatTimeUi(true) and +07:00
    //auto mouseTimeQDT = QDateTime().fromString("1970-01-01T00:00:00", Qt::ISODate).addMSecs(static_cast<qint64>(time*1000));

    auto mouseTimeQDT = keyToDateTime(key);
    auto mouseTimeStr = mouseTimeQDT.toString(EasyLiving::formatTimeUi(false));

    if (dayStyle())
    {
        return mouseTimeQDT.toString(EasyLiving::formatDateTimeUi());
    }

    if (cursor2Visible())
    {
        auto begin = keyToDateTime(_cursor->start->key());
        auto end = keyToDateTime(_cursor2->start->key());

        return QString("%1 [%2]")
                .arg(mouseTimeStr)
                .arg(EasyLiving::dateTimeDelta(begin, end, false));
    }
    else
    {
        auto now = QDateTime::currentDateTime();
        auto deltaTimeMSEC = now.msecsTo(mouseTimeQDT);
        //qDebug() << deltaTimeMSEC;
        if (deltaTimeMSEC > -3000 ) // 3 sec
            return mouseTimeStr;

        return QString("%1 (-%2)")
                .arg(mouseTimeStr)
                .arg(EasyLiving::dateTimeDelta(mouseTimeQDT, now, false));
    }
}

bool RealTimePlot::isInAxisRect(QPoint pos)
{
    return qcp()->axisRect()->rect().contains(pos);
}
