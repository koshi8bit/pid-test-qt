#include "shared-variable.h"
#include <typeinfo>



QUdpSocket * AbstractSharedVariable::socket = nullptr;
QUdpSocket * AbstractSharedVariable::writeSocket = nullptr;

QList<AbstractSharedVariable*> AbstractSharedVariable::variables;

int AbstractSharedVariable::_port = -1;

int AbstractSharedVariable::variablesCounter = 0;


AbstractSharedVariable::AbstractSharedVariable(QObject *parent) : QObject(parent)
{
    if(socket == nullptr){
        socket = new QUdpSocket(0);
        writeSocket = new QUdpSocket(0);
        if(_port != -1){
            if(socket->bind(QHostAddress::Any,_port)){
                connect(socket,&QUdpSocket::readyRead,handleMessage);
            }else{
                qDebug() << "AbstractNetworkVariable::AbstractNetworkVariable bind failed";
                emit errorOcurred("AbstractNetworkVariable::AbstractNetworkVariable bind failed");
            }
        }else{
            qDebug() << "AbstractNetworkVariable::AbstractNetworkVariable bad port. Did You call AbstractSharedVariable::setPort(..)?";
            emit errorOcurred("AbstractNetworkVariable::AbstractNetworkVariable bad port. Did You call AbstractSharedVariable::setPort(..)?");
        }
    }
    variablesCounter++;

}

AbstractSharedVariable::~AbstractSharedVariable()
{
    variablesCounter--;
    if(variablesCounter == 0){
        socket->deleteLater();
        socket = nullptr;
    }
}

void AbstractSharedVariable::setPort(int port)
{
    _port = port;
}

void AbstractSharedVariable::handleMessage()
{
    while (socket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
        QByteArrayList list = datagram.split(':');
        if(list.count() == 2){
            int varId = -1;
            for(int i = 0; i < variables.count(); i++){
                uint hashName = *((uint*)list.at(0).data());
                if(qHash(variables.at(i)->networkName) == hashName){
                    varId = i;
                    break;
                }
            }
            if(varId == -1){
                qDebug() << "an unknown variable is received";
                return;
            }
            if(variables.at(varId)->undecodedValue == nullptr){
                variables.at(varId)->undecodedValue = new char[list.at(1).length()];
            }
            for(int i = 0; i < list.at(1).length(); i++){
                variables.at(varId)->undecodedValue[i] = list.at(1).data()[i];
            }
            variables.at(varId)->decodeValue();
        }else{
            qDebug() << "datagram.count is not 2";
        }
    }
}

