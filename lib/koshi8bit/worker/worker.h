#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include <lib/koshi8bit/easyliving.h>


class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QString name, Qt::ConnectionType connectionType=Qt::ConnectionType::AutoConnection);
    ~Worker();
    std::function<void()> heavyWork;

    bool isCycleBusy() const;

    bool isBusy() const;
    QString lastError="";

private:
    QThread *thread;
    QTimer *timer;
    QTimer *timerSingleTime;
    QString name;
    bool _isCycleBusy = false;

signals:
    void heavyWorkSingleTimeFinished();
    void heavyWorkFinished();
    //void progressChanged(int progress);

public slots:
    void start();
    void start(int intervalMSEC);

    void stop(bool forseStop = false);

private slots:
    void timerTimeout();
    void timerTimeoutSingleTime();

};

#endif // WORKER_H
