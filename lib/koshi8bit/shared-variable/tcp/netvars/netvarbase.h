#ifndef NETVARBASE_H
#define NETVARBASE_H

#include <QObject>
#include <QString>
#include "nvDebug.h"
#include <QVariant>
#include <QReadWriteLock>

class NetVarBase : public QObject
{
    Q_OBJECT
    NetVarBase();
    NetVarBase(NetVarBase &other);
    NetVarBase &operator=(const NetVarBase &other);
public:
    NetVarBase(QString networkName);
    virtual ~NetVarBase();
    bool operator==(NetVarBase &other);
    QString name;
    void updateNewValue(QVariant value);
signals:
    void valueChanged();
    void errorOccurred(QString message);
public slots:
    void ask();
    void send();
protected:
    QVariant _value;
    QReadWriteLock l;


    friend class VarsContainer;
    friend class InitNVServer;
    friend class InitNVClient;
};

#endif // NETVARBASE_H
