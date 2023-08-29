#include "log.h"

Log::Log(QObject *parent) : QObject(parent)
{
    timerCommit = new QTimer;
    timerCommit->setInterval(intervalCommitMSEC);
    connect(timerCommit, &QTimer::timeout, this, &Log::timeoutCommit, Qt::ConnectionType::QueuedConnection);

    timerPush = new QTimer;
    timerPush->setInterval(intervalPushSEC*1000);
    connect(timerPush, &QTimer::timeout, this, &Log::timeoutPush, Qt::ConnectionType::QueuedConnection);

    thread = new QThread();
    this->moveToThread(thread);
    thread->start();
}

Log::~Log()
{
    thread->terminate();

    timerCommit->deleteLater();
    timerPush->deleteLater();

    thread->deleteLater();
}

void Log::addChannel(Channel *channel)
{
    channels.append(channel);
}

void Log::finishConfigure()
{
    if (!configureFinished)
    {
        finishConfigureChild();
        configureFinished = true;
    }
}


void Log::setAutoLog(bool newValue)
{

    if (newValue)
    {
        finishConfigure();
        timerCommit->start();
        timerPush->start();
    }
    else
    {
        timerCommit->stop();
        timerPush->stop();
    }
}

void Log::timeoutCommit()
{
    commit();
}

void Log::timeoutPush()
{
    push();
}
