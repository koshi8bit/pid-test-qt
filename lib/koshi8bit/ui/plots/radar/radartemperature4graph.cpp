#include "radartemperature4graph.h"


RadarTemperature4Graph::RadarTemperature4Graph(const QString &label, QColor color,
    QCustomPlot *qcp, ChannelDouble *up, ChannelDouble *right, ChannelDouble *down,
    ChannelDouble *left, int precision, bool scientificNotation, int lineWidth)
    :RadarGraph(label, EasyLiving::postfixCelsius(), color, qcp, precision,
                scientificNotation, lineWidth)
{
    this->up = up;
    this->right = right;
    this->down = down;
    this->left = left;
    calcDeviation();
    updateLegendItem();
}

void RadarTemperature4Graph::calcDeviation()
{
    auto dx = right->value() - left->value();
    auto dy = up->value() - down->value();

    auto radius = qSqrt(dx * dx + dy * dy);
    auto angleRad = qAtan2(dy, dx);
    auto angleDeg = (angleRad * 180 / M_PI) + rotationOffset();

    setValue(radius, angleDeg);
}

double RadarTemperature4Graph::rotationOffset() const
{
    return _rotationOffset;
}

void RadarTemperature4Graph::setRrotationOffset(double rotationOffset)
{
    _rotationOffset = rotationOffset;
}

int RadarTemperature4Graph::legendPrecision() const
{
    return _legendPrecision;
}

void RadarTemperature4Graph::setLegendPrecision(int legendPrecision)
{
    _legendPrecision = legendPrecision;
}

void RadarTemperature4Graph::updateLegendItem()
{
    if (visible())
    {
        auto text = QString("%1: %2%3 [В%4 П%5 Н%6 Л%7]")
                .arg(label())
                .arg(EasyLiving::formatDouble(radius(), precision()))
                .arg(postfix())
                .arg(EasyLiving::formatDouble(up->value(), legendPrecision()))
                .arg(EasyLiving::formatDouble(right->value(), legendPrecision()))
                .arg(EasyLiving::formatDouble(down->value(), legendPrecision()))
                .arg(EasyLiving::formatDouble(left->value(), legendPrecision()));
        legendItem()->setLabelText(text);
    }
}
