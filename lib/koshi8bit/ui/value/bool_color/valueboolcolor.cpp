
#include "valueboolcolor.h"

ValueBoolColor::ValueBoolColor(QWidget *parent)
    : QPushButton(parent)
{

}

void ValueBoolColor::configure(QString textOn, QString textOff, QString moduleName)
{
    this->setCheckable(true);
    toolTipDisconnected = QString("Нет связи с '%1'").arg(moduleName);
    this->textOn = textOn;
    this->textOff = textOff;
    //setStyleSheet(QString("QPushButton:disabled{background-color:%1;}").arg(QColor(255, 0, 0).name()));
    _toggled(isChecked());

    connect(this, &QPushButton::toggled,
            this, &ValueBoolColor::_toggled);

}

void ValueBoolColor::setColor(QColor on, QColor off, QColor disconnected)
{
    styleSheetOn = buildStyleSheet(on);
    styleSheetOff = buildStyleSheet(off);
    styleSheetDisconnected = buildStyleSheet(disconnected);
}

QString ValueBoolColor::buildStyleSheet(QColor color)
{
    if (color.isValid()) {
        return QString("background-color: %1").arg(color.name());
    } else {
        return "";
    }
}

bool ValueBoolColor::connected() const
{
    return _connected;
}

void ValueBoolColor::setConnected(bool connected)
{
    _connected = connected;
    setEnabled(connected);
    if (connected) {
        _toggled(isChecked());
    } else {
        setToolTip(toolTipDisconnected);
        setChecked(false);
        setText("⚠");
        setStyleSheet(styleSheetDisconnected);
    }

}

void ValueBoolColor::_toggled(bool checked)
{
    auto toolTip = QString("Текущее состояние: '%1'");
    if (checked) {
        setText(textOn);
        setStyleSheet(styleSheetOn);
        setToolTip(toolTip.arg(textOn));
    } else {
        setText(textOff);
        setStyleSheet(styleSheetOff);
        setToolTip(toolTip.arg(textOff));
    }

}

