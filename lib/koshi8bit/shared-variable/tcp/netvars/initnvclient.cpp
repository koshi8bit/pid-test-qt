#include "initnvclient.h"
#include <QReadWriteLock>
#include <QWriteLocker>

QTcpSocket * InitNVClient::tcpclient = nullptr;
QDataStream InitNVClient::in;

void InitNVClient::ask(QString name)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << tr("Ask");
    out << name;
    InitNVClient::tcpclient->write(block);
    InitNVClient::tcpclient->flush();
}

void InitNVClient::sendValue(QString name, QVariant value)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << tr("NewValue");
    out << name;
    out << value;
    InitNVClient::tcpclient->write(block);
    InitNVClient::tcpclient->flush();
}

void InitNVClient::setValFor(int id, QString name, QVariant value)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << tr("SetValueFor");
    out << id;
    out << name;
    out << value;
    InitNVClient::tcpclient->write(block);
    InitNVClient::tcpclient->flush();
}

InitNVClient::InitNVClient(QString serverIp, quint16 serverPort, int autoReconnectTimeMs)
    : VarsContainer(nullptr),
     serverIp(serverIp),
     serverPort(serverPort)
{
    if(!tcpclient){
        tcpclient = new QTcpSocket(nullptr);
        if(autoReconnectTimeMs != 0){
            t.setInterval(autoReconnectTimeMs);
            connect(&t,&QTimer::timeout,this,&InitNVClient::connectToServer);
            autoReconnectMode = true;
        }
        in.setDevice(tcpclient);
        in.setVersion(QDataStream::Qt_5_10);

        connect(tcpclient, &QTcpSocket::readyRead, this, &InitNVClient::readFullMessage);
        connect(tcpclient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(getError(QAbstractSocket::SocketError)));
        connect(tcpclient, &QTcpSocket::connected,this, &InitNVClient::stopAutoReconnect);
        connect(tcpclient, &QTcpSocket::connected,this, &InitNVClient::onConnect);
        connectToServer();
    }
}

InitNVClient::~InitNVClient()
{
    if(tcpclient){
        tcpclient->close();
        tcpclient->deleteLater();
    }
    tcpclient = nullptr;
}

void InitNVClient::connectToServer()
{
    tcpclient->abort();
    tcpclient->connectToHost(serverIp,serverPort);
#ifdef KOSHI8BIT_LIB_SV_SHOW_DEBUG
    nvDebug << "Connecting to" << serverIp << serverPort;
#endif
}

void InitNVClient::readFullMessage()
{
    while(!in.atEnd()){
        in.startTransaction();
        QString command;
        in >> command;
        if(command == "SetValue"){
            QString varName;
            in >> varName;
            QVariant value;
            in >> value;
            if (!in.commitTransaction())
                return;

            updateLocalVar(varName,value);
        }else
        if(command == "AskFor"){
            int id = -2;
            in >> id;
            QString varName;
            in >> varName;
            if (!in.commitTransaction())
                return;
            if(id == -2){
                nvDebug << "OH SHEET A RAT!";
                return;
            }
            int i = localVarsIdByName(varName);
            if(i != -1){
                setValFor(id,varName,localVars.at(i)->_value);
            }
        }else{
            nvDebug << "unknown command" << command;
            in.abortTransaction();
            break;
        }
    }
}

void InitNVClient::getError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
         case QAbstractSocket::RemoteHostClosedError:
            nvDebug << "RemoteHostClosedError";
            break;
         case QAbstractSocket::HostNotFoundError:
             nvDebug << "The host was not found. Please check the host name and port settings.";
             break;
         case QAbstractSocket::ConnectionRefusedError:
             nvDebug << "The connection was refused by the peer.";
             break;
         default:
            #ifdef KOSHI8BIT_LIB_SHARED_VARIABLE_ENABLE_NVDEBUG
            nvDebug << "wait oh shee";
            #endif
            ;

    }
    nvDebug << tcpclient->errorString();
    emit disConnected();
    emit connectionChanged(false);
    if(autoReconnectMode)
        t.start();
}

void InitNVClient::stopAutoReconnect()
{
    if(autoReconnectMode)
        t.stop();
}

void InitNVClient::onConnect()
{
#ifndef KOSHI8BIT_LIB_SV_HIDE_MESSAGES
    nvDebug << "Connected.";
#endif
    emit connected();
    emit connectionChanged(true);
}
