#include "netclient.h"


NetClient::NetClient()
{
    id = -1;
    socket = nullptr;
    socketOwner = false;
}

NetClient::NetClient(const NetClient &other) : QObject(nullptr)
{
    NetClient(other.id,other.socket);
    socketOwner = false;
}

bool NetClient::operator==(const NetClient &other)
{
    return id == other.id;
}

NetClient::NetClient(int id, QTcpSocket *socket) : QObject(nullptr), socket(socket),id(id)
{
    inputStream.setDevice(socket);
    inputStream.setVersion(QDataStream::Qt_5_10);


    connect(socket, &QAbstractSocket::disconnected,this,&NetClient::socketDisconected);
    connect(socket, &QTcpSocket::readyRead,this,&NetClient::receiveFullMessage);
}

NetClient::~NetClient()
{
    if(socketOwner){
        socket->deleteLater();
    }
}

int NetClient::getId()
{
    return id;
}

void NetClient::sendNewValue(QString varName,QVariant value)
{  
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << tr("SetValue");
    out << varName;
    out << value;
    if(socket->write(block) == -1){
        nvDebug << "could not send new value, somth went wrong";
        nvDebug << socket->errorString();
    }
}

void NetClient::askFor(int id, QString varName)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << tr("AskFor");
    out << id;
    out << varName;
    if(socket->write(block) == -1){
        nvDebug << "could not send new value, somth went wrong";
        nvDebug << socket->errorString();
    }
}


void NetClient::receiveFullMessage()
{
    while(!inputStream.atEnd()){
        inputStream.startTransaction();
        QString command;
        inputStream >> command;
        if(command == "NewValue"){
            QString varName;
            inputStream >> varName;
            QVariant value;
            inputStream >> value;
            if(!inputStream.commitTransaction())
                return;
            emit newValue(id,varName,value);
        }else
        if(command == "Ask"){
            QString varName;
            inputStream >> varName;
            if(!inputStream.commitTransaction())
                return;
            emit ask(varName);
        }else
        if(command == "SetValueFor"){
            int idToSend = -2;
            inputStream >> idToSend;
            QString varName;
            inputStream >> varName;
            QVariant value;
            inputStream >> value;

            if(!inputStream.commitTransaction())
                return;

            emit setValueFor(idToSend,varName,value);
        }else{
            inputStream.abortTransaction();
            break;
        }
    }
}

void NetClient::sendMessage(QString msg)
{
    //TODO: remove this;
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << msg;
    if(socket->write(block) == -1){
        nvDebug << "could not send new value, somth went wrong";
        nvDebug << socket->errorString();
    }
}
