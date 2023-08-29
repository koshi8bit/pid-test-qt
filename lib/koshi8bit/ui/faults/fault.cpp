#include "fault.h"

Fault::Fault(QStringList prefix, QString text, QObject *parent)
    : QObject(parent)
{
    _message = QString("%1: %2")
            .arg(Channel::pathJoin(prefix))
            .arg(text);

    _widget = new QLabel(message());
    setVisible(false);


}

Fault::Fault(QString message, QObject *parent)
    : QObject(parent)
{
    _message = message;

    _widget = new QLabel(message);
    setVisible(false);
}

QWidget *Fault::widget() const
{
    return _widget;
}

bool Fault::isVisible()
{
    return _isVisible; //_widget->isVisible();
}

QString Fault::message() const
{
    return _message;
}

void Fault::setVisible(bool visible)
{
    _widget->setVisible(visible);
    _isVisible = visible;
    emit visibleChanged(visible);
}
