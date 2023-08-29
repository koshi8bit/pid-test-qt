
#ifndef VALUEBOOLCOLOR_H
#define VALUEBOOLCOLOR_H

#include <QPushButton>
#include <QDebug>
#include <lib/koshi8bit/easyliving.h>


class ValueBoolColor : public QPushButton
{
public:
    ValueBoolColor(QWidget *parent = nullptr);
    void configure(QString textOn, QString textOff, QString moduleName = "<not set>");
    //void setColor(QColor on, QColor off = QColor(), QColor disconnected = QColor(255, 0, 0));
    void setColor(QColor on, QColor off = QColor(), QColor disconnected = QColor());


    bool connected() const;
    void setConnected(bool newConnected);

private:
    QString textOn, textOff, toolTipDisconnected="";
    QString styleSheetOn, styleSheetOff, styleSheetDisconnected;
    QString buildStyleSheet(QColor color);
    bool _connected;

private slots:
    void _toggled(bool checked = false);
};

#endif // VALUEBOOLCOLOR_H
