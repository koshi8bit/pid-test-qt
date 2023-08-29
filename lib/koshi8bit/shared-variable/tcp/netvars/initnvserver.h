#ifndef INITNVSERVER_H
#define INITNVSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "netclient.h"
#include "netvarbase.h"
#include "varscontainer.h"

class InitNVServer : public VarsContainer
{
    Q_OBJECT
    static QTcpServer * tcpserver;
    static QList<NetClient*> clients;
    static void sendToAll(QString varName,QVariant value);
    static void askAll(QString varName);

    InitNVServer();
signals:
    void newConnection(NetClient *client);
    void clientDisconnected();
public:

    int lastId = 0;
    NetClient *clientById(int id);
    InitNVServer(quint16 port);
    virtual ~InitNVServer();

public slots:

private slots:
    void saveNewClient();
    void deleteClient();
    void newValueForAll(int idNotToSend, QString varName, QVariant value);
    void clientIsAsking(QString varName);
    void clientsSetValueFor(int idToSend,QString varName,QVariant value);


    friend class NetVarBase;
};

#endif // INITNVSERVER_H
