#include "worker.h"


Worker::Worker(QString name, Qt::ConnectionType connectionType)
    :QObject()
{
    this->name = name;
    thread = new QThread();
    this->moveToThread(thread);
    thread->start();

    timer = new QTimer();
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout,
            this, &Worker::timerTimeout,
            connectionType);

    timerSingleTime = new QTimer();
    timerSingleTime->setInterval(0);
    timerSingleTime->setSingleShot(true);
    connect(timerSingleTime, &QTimer::timeout,
            this, &Worker::timerTimeoutSingleTime,
            connectionType);

}

Worker::~Worker()
{
    timer->stop();
    thread->terminate(); //TODO quit

    timer->deleteLater();
    timerSingleTime->deleteLater();
    thread->deleteLater();
}

bool Worker::isCycleBusy() const
{
    return _isCycleBusy;
}

bool Worker::isBusy() const
{
    return isCycleBusy() || timer->isActive();
}

void Worker::start()
{
    if (isCycleBusy())
    {
        qWarning() << EL_FORMAT_ERR("Cycle is not finished yet. Abort.");
        return;
    }

    timerSingleTime->start();
}

void Worker::start(int intervalMSEC)
{
    timer->setInterval(intervalMSEC);
    //FIXME если процесс занимает больше времени, чем интервал - то на стеке он будет копиться.
    //мб вообще нах таймер?
    //timer->setSingleShot(true);

    timer->start();
}

void Worker::stop(bool forseStop)
{
    Q_UNUSED(forseStop)
    //qCritical() << EL_FORMAT_ERR("Not implemented yet");

    timer->stop();
    timerSingleTime->stop();
}

void Worker::timerTimeout()
{
//    if (!isCycleFinished())
//        return;

    _isCycleBusy = true;
    heavyWork();
    _isCycleBusy = false;
    emit heavyWorkFinished();

    //timer->start();
}

void Worker::timerTimeoutSingleTime()
{
    _isCycleBusy = true;
    heavyWork();
    _isCycleBusy = false;
    emit heavyWorkSingleTimeFinished();
}



