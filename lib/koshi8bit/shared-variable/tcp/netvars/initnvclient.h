#ifndef INITNVCLIENT_H
#define INITNVCLIENT_H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include "nvDebug.h"
#include "varscontainer.h"

class InitNVClient : public VarsContainer
{
    Q_OBJECT
    static QTcpSocket * tcpclient;
    static QDataStream in;
    static void ask(QString name);
    static void sendValue(QString name,QVariant value);
    static void setValFor(int id,QString name,QVariant value);
    QTimer t;
    InitNVClient();
public:
    InitNVClient(QString serverIp, quint16 serverPort, int autoReconnectTimeMs = 0);
    virtual ~InitNVClient();

signals:
    void connected();
    void connectionChanged(bool state);
    void disConnected();
public slots:
    void connectToServer();
    void readFullMessage();
    void getError(QAbstractSocket::SocketError socketError);
    void stopAutoReconnect();
    void onConnect();
protected:
    QString serverIp;
    quint16 serverPort;
    bool autoReconnectMode = false;

friend class NetVarBase;

};

#endif // INITNVCLIENT_H
