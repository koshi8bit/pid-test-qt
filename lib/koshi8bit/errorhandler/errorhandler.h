#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTimer>

#include <lib/koshi8bit/easyliving.h>

class ErrorHandler : public QObject
{
    Q_OBJECT
public:
    explicit ErrorHandler(QObject *parent = nullptr);
    QTimer *timer;

    void checkForErrors();

private:
    static const QString errorSave;
    static const QString errorSend;
    static const QString okSend;
    bool triggered = false;
    bool checkForErrorsEmited = false;



//    QFile *file;
//    QTextStream *stream;

    void showErrorMessage(QString messageToUser, QString error);


signals:

public slots:
    void processError(QString error);

private slots:
    void timerTimeout();
};

#endif // ERRORHANDLER_H
