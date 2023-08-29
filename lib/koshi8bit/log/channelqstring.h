#ifndef CHANNELQSTRING_H
#define CHANNELQSTRING_H

#include "channelt.h"

class ChannelQString : public ChannelT<QString>
{
public:
    Q_OBJECT
public:
    ChannelQString(QString name, QString postfix, QObject *parent = nullptr);
    ChannelQString(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);
    ChannelQString(QString sharedVariableName, QObject *parent = nullptr);

    bool isLogged();
    void valueReadByLogger();

private:
    bool _isLogged = false;


    // ChannelT interface
protected:
    void valueSetChild() override;

};

#endif // CHANNELQSTRING_H
