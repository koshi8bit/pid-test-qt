#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include "nvDebug.h"

class NetClient : public QObject
{
    Q_OBJECT
public:
    NetClient();
    NetClient(const NetClient &other);
    bool operator==(const NetClient &other);
    NetClient(int id,QTcpSocket *socket);
    virtual ~NetClient();
    int getId();
    void sendNewValue(QString varName, QVariant value);
    void askFor(int id,QString varName);
    QTcpSocket *socket;
    int id;
signals:
    void socketDisconected();
    void setValueFor(int id,QString varName,QVariant value);
    void newValue(int idNotToSend,QString varName,QVariant value);
    void ask(QString varName);
private slots:
    void receiveFullMessage();
    //void getReadyToDisconnect();
private:
    void sendMessage(QString msg);

    QDataStream inputStream;
    bool socketOwner = true;
};

#endif // NETCLIENT_H
