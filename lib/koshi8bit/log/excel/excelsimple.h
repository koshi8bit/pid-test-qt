#ifndef EXCELSIMPLE_H
#define EXCELSIMPLE_H

#include "excel.h"

class ExcelSimple : public QObject
{
public:
    ExcelSimple(QString filename, QObject *parent = nullptr);
    ExcelSimple(QString filename, bool pushOnCommit, bool clearBeforeStart, QString codepage="", QObject *parent = nullptr);

    void configure(QString filename);

    void commit(QStringList list);
    void commit(QList<double> list);
    //void commit(QList<QString> list);
    void commit(QString line);

    bool push();

    bool pushOnCommit() const;
    void setPushOnCommit(bool pushOnCommit);

private:
    QString filename, codepage;
    bool _pushOnCommit;

    QString buffer;
};

#endif // EXCELSIMPLE_H
