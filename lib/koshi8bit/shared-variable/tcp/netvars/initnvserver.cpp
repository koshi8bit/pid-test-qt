#include "initnvserver.h"

QTcpServer * InitNVServer::tcpserver = nullptr;
QList<NetClient*> InitNVServer::clients;

NetClient *InitNVServer::clientById(int id)
{
    for(int i = 0; i < clients.count(); i++){
        if(id == clients.at(i)->id){
            return clients.at(i);
        }
    }
    return nullptr;
}

InitNVServer::InitNVServer(quint16 port) : VarsContainer(nullptr)
{
    if(!tcpserver){
        tcpserver = new QTcpServer(nullptr);

        if(tcpserver->listen(QHostAddress::Any,port)){
#ifdef KOSHI8BIT_LIB_SV_SHOW_DEBUG
            nvDebug << "Listening on" << port << "port";
#endif
        }else{
            nvDebug << "Could not host the server, try another port";
            nvDebug << tcpserver->errorString();
        }

        connect(tcpserver,SIGNAL(newConnection()),this, SLOT(saveNewClient()));
    }else{
        nvDebug << "Server is already constructed";
    }
}

InitNVServer::~InitNVServer()
{
    if(tcpserver){
        tcpserver->close();
        tcpserver->deleteLater();
    }
    tcpserver = nullptr;
}

void InitNVServer::sendToAll(QString varName, QVariant value)
{
    for(int i = 0; i < clients.count(); i++){
        clients.at(i)->sendNewValue(varName,value);
    }
}

void InitNVServer::askAll(QString varName)
{
    for(int i = 0; i < clients.count(); i++){
        clients.at(i)->askFor(-1,varName);
    }
}

void InitNVServer::saveNewClient()
{
    QTcpSocket *clientSocket = tcpserver->nextPendingConnection();

    nvDebug << "New client" << clientSocket->peerAddress().toString() << clientSocket->peerPort();
    NetClient *newClient = new NetClient(lastId,clientSocket);
    lastId++;
    connect(newClient,&NetClient::socketDisconected,this,&InitNVServer::deleteClient);
    connect(newClient,&NetClient::socketDisconected,this,&InitNVServer::clientDisconnected);
    connect(newClient,&NetClient::newValue,this,&InitNVServer::newValueForAll);
    connect(newClient,&NetClient::ask,this,&InitNVServer::clientIsAsking);
    connect(newClient,&NetClient::setValueFor,this,&InitNVServer::clientsSetValueFor);
    clients.append(newClient);
    emit newConnection(newClient);
}

void InitNVServer::deleteClient()
{
    NetClient *client = static_cast<NetClient*>(QObject::sender());
    nvDebug << "Client disconected" << client->socket->peerAddress().toString() << client->socket->peerPort();
    clients.removeOne(client);
    client->deleteLater();
}

void InitNVServer::newValueForAll(int idNotToSend,QString varName, QVariant value)
{
    for(int i = 0; i < clients.count(); i++){
        if(clients.at(i)->getId() != idNotToSend)
            clients.at(i)->sendNewValue(varName,value);
    }
    updateLocalVar(varName,value);
}

void InitNVServer::clientIsAsking(QString varName)
{
    NetClient *client = static_cast<NetClient*>(QObject::sender());
    int iVar = VarsContainer::localVarsIdByName(varName);
    if(iVar != -1){
        client->sendNewValue(varName,VarsContainer::localVars.at(iVar)->_value);
    }else{
        for(int i = 0; i < clients.count(); i++){
            if(clients.at(i)->getId() != client->id)
                clients.at(i)->askFor(client->id,varName);
        }
    }
}

void InitNVServer::clientsSetValueFor(int idToSend, QString varName, QVariant value)
{
    if(idToSend != -1){
        NetClient *client = clientById(idToSend);
        if(client != nullptr){
            client->sendNewValue(varName,value);
        }
    }else{
        updateLocalVar(varName,value);
    }
}
