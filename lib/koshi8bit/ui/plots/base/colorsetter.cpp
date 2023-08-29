#include "colorsetter.h"

ColorSetter::ColorSetter(QObject *parent) : QObject(parent)
{
    colors = new QList<QColor>();
    resetColors();
}

QColor ColorSetter::getColor(bool random)
{
    if (random)
    {
        return QColor::fromRgb(QRandomGenerator::global()->generate());
    }
    else
    {
        auto index = currentIndex % colors->count();
        currentIndex += 1;
        return colors->at(index);
    }
}

void ColorSetter::resetColors()
{
    colors->append(QColor("#FFFFFF"));
    colors->append(QColor("#FF4242"));
    colors->append(QColor("#0EFF00"));
    colors->append(QColor("#42C2FF"));
    colors->append(QColor("#D2FF71"));
    colors->append(QColor("#CD59FF"));
    colors->append(QColor("#FFB312"));
    colors->append(QColor("#4245FF"));
    colors->append(QColor("#FF42B6"));
    colors->append(QColor("#59FFF4"));
}


