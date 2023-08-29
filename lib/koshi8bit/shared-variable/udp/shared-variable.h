#ifndef NETWORKVARIABLE_H
#define NETWORKVARIABLE_H

#include <QObject>
#include <QUdpSocket>


class AbstractSharedVariable : public QObject
{
    Q_OBJECT
public:
    static void setPort(int port);

    explicit AbstractSharedVariable(QObject *parent = 0);
    virtual ~AbstractSharedVariable();


signals:
    void valueChanged();
    void errorOcurred(QString message);

public slots:

private slots:
    static void handleMessage();
    virtual void decodeValue() = 0;

protected:
    static QList<AbstractSharedVariable*> variables;
    static QUdpSocket *socket;
    static QUdpSocket *writeSocket;
    static int _port;

    static int variablesCounter;
    QString networkName;
    char *undecodedValue = nullptr;

};


template<typename T>
class SharedVariable: public AbstractSharedVariable
{
public:

    explicit SharedVariable(QString networkName,QObject *parent = 0): AbstractSharedVariable(parent)
    {
        this->networkName = networkName;
        variables.append(this);
    }

    ~SharedVariable()
    {
        variables.removeOne(this);
    }

    T value()
    {
        return _value;
    }

    void addClient(QString ip,int port)
    {
        QPair<QString,int> pair;
        pair.first = ip;
        pair.second = port;
        clients.append(pair);
    }

    void synchronize()
    {
        uint hash = qHash(networkName);
        char* hashName = new char[sizeof(uint)];
        hashName = (char*)&hash;

        char *bytesValue = new char[sizeof(_value)];
        bytesValue = (char*)&_value;

        for(int i = 0; i < clients.count(); i++){
            QByteArray byteName(hashName,sizeof(uint));
            QByteArray byteValue(bytesValue,sizeof(_value));

            QByteArray datagram = byteName + ":" +byteValue;

            writeSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress(clients.at(i).first),clients.at(i).second);
        }
    }

    void setValue(T newValue)
    {
        _value = newValue;
        emit valueChanged();
    }


private:
    T _value;
    QList<QPair<QString,int>> clients;

    void decodeValue()
    {
        _value = *((T*)undecodedValue);
        emit valueChanged();
    }





};

#endif // NETWORKVARIABLE_H
