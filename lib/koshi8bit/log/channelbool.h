#ifndef CHANNELBOOL_H
#define CHANNELBOOL_H

#include "channelrealtimegraph.h"

class ChannelBool : public ChannelRealTimeGraph<bool>
{
    Q_OBJECT
public:
    ChannelBool(QString name, QString postfix, QObject *parent = nullptr);
    ChannelBool(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);
    ChannelBool(QString sharedVariableName, QObject *parent = nullptr);
    ~ChannelBool() override;

private:

    bool _inverted = false;
    void configure();

signals:
    //TODO: template fuck
    //void valueChangedDouble(double newValue);

protected:
    void valueSetChild() override;
};

#endif // CHANNELBOOL_H
