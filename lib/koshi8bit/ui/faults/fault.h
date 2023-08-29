#ifndef FAULT_H
#define FAULT_H

#include <QObject>
#include <QWidget>
#include <QLabel>

#include <lib/koshi8bit/log/channel.h>

class Fault : public QObject
{
    Q_OBJECT
public:
    explicit Fault(QStringList prefix, QString text, QObject *parent = nullptr);
    explicit Fault(QString message, QObject *parent = nullptr);

    QWidget *widget() const;
    bool isVisible();

    QString message() const;

private:
    QWidget* _widget;
    QString _message;
    bool _isVisible=false;

public slots:
    void setVisible(bool visible);


signals:
    void visibleChanged(bool visible);

};

#endif // FAULT_H
