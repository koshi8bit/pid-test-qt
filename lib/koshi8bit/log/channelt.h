#ifndef CHANNELT_H
#define CHANNELT_H

#include <QStringList>

#include "channel.h"
#include <lib/koshi8bit/shared-variable/tcp/netvars.h>

template <typename T>
class ChannelT : public Channel
{
public:
    ChannelT(QString name, QString postfix, QObject *parent = nullptr)
        :Channel(name, postfix, parent)
    {
        init();
    }

    ChannelT(QString name, QString postfix, QStringList &path, QObject *parent = nullptr)
        :Channel(name, postfix, path, parent)
    {
        init();
    }

    ChannelT(QString sharedVariableName, QObject *parent = nullptr)
        :Channel(getName(sharedVariableName), "", parent)
    {
        //FIXME for what?? parent do same thing??
        setLogName(sharedVariableName);

        init();

        //configure and get postfix
        //setPostfix=???

        configureSharedVariable(true);
        askSharedVariable();
    }

    void init()
    {
        _value = T();
    }

    ~ChannelT()
    {
        if (sharedVariable)
            sharedVariable->deleteLater();
    }

    virtual T value()
    {
        return _value;
    }

    bool enableWriteFromNet() const
    {
        return _enableWriteFromNet;
    }

//    void configureSharedVariableTimer()
//    {
//        sharedVariableSendTimer = new QTimer();
//        sharedVariableSendTimer->setSingleShot(true);

//        connect(sharedVariableSendTimer, &QTimer::timeout,
//                sharedVariable, &NetVarBase::send, Qt::QueuedConnection);
//    }

    QString configureSharedVariable(bool enableWriteFromNet = false)
    {
        sharedVariable = new NetVar<T>(logName());
        _enableWriteFromNet = enableWriteFromNet;

        if (enableWriteFromNet)
        {
            connect(sharedVariable, &NetVarBase::valueChanged,
                    this, &ChannelT::sharedVariableUpdated);
        }
        else
        {
            disconnect(sharedVariable, &NetVarBase::valueChanged,
                       this, &ChannelT::sharedVariableUpdated);
        }

#ifdef KOSHI8BIT_LIB_CHANNELS_SHOW_SV_CREATED
        qDebug() << "sharedVariable" << logName() << "created";
#endif
        return logName();
    }

    void askSharedVariable()
    {
        sharedVariable->ask();
    }

    bool getEnableWriteFromNet() const;

public slots:
    void setValue(T newValue)
    {
        _setValue(newValue);

        // TODO do not work from diff thread
        if (sharedVariable)
        {
            sharedVariable->setValue(newValue);
            sharedVariable->send();
            //sharedVariableSendTimer->start(0);
        }
    }

private slots:
    void updateSharedVariable()
    {
        sharedVariable->setValue(value());
        sharedVariable->send();
        //sharedVariableSendTimer->start(0);
    }

protected:

private:
    T _value;

    //QTimer *sharedVariableSendTimer;

    NetVar<T> *sharedVariable = nullptr;
    bool _enableWriteFromNet = false;

    void _setValue(T newValue)
    {
        _value = newValue;
        valueSetChild();

        //qDebug() << "valueChanged" << logName() << newValue;
        emit valueChanged();
//      emit valueChanged777(_value);
    }

    static QString getName(QString sharedVariableName)
    {
        return sharedVariableName.split("/").last();
    }

    void sharedVariableUpdated()
    {
        _setValue(sharedVariable->value());
        emit valueChangedByNet();
    }

protected:
    virtual void valueSetChild()
    {

    }


//    void valueChanged777(T newValue);

};


#endif // CHANNEL_H


