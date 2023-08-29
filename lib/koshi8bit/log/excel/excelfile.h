#ifndef EXCELFILE_H
#define EXCELFILE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDateTime>

#include <lib/koshi8bit/easyliving.h>

class ExcelFile : public QObject
{
    Q_OBJECT
public:
    explicit ExcelFile(QObject *parent = nullptr);
    ~ExcelFile();

    bool configure(QDateTime dt, QString datePattern, QString folder, QString codepage="");
    void append(QString message);

    bool push();
    bool isCreated();
    QString fileName();


private:
    QFile *file = nullptr;
    QTextStream *stream;
    QString buffer, codepage;
    bool _isCreated;

    bool openFile();


    long long tryPush();
    
signals:
    void errorOcurred(QString message);

public slots:
};

#endif // EXCELFILE_H
