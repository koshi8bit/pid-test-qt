#include "channelqstring.h"

ChannelQString::ChannelQString(QString name, QString postfix, QObject *parent)
    :ChannelT<QString>(name, postfix, parent)
{
}

ChannelQString::ChannelQString(QString name, QString postfix, QStringList &path, QObject *parent)
    :ChannelT<QString>(name, postfix, path, parent)
{
}

ChannelQString::ChannelQString(QString sharedVariableName, QObject *parent)
    :ChannelT<QString>(sharedVariableName, parent)
{
}

bool ChannelQString::isLogged()
{
    return _isLogged;
}

void ChannelQString::valueReadByLogger()
{
    _isLogged = true;
}

void ChannelQString::valueSetChild()
{
    _isLogged = false;
}

