#include "gradientlineedit.h"

GradientLineEdit::GradientLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setAlignment(Qt::AlignCenter);
}

void GradientLineEdit::configure()
{
    configureRange();
    configureGradient();
    display(0);
}

void GradientLineEdit::configure(QCPRange *range, QCPColorGradient *gradient)
{
    setRange(range, false);
    setGradient(gradient, false);
    display(0);
}

void GradientLineEdit::configureRange()
{
    _range = new QCPRange(0, 0);
    //FIXME tima45
    //emit rangeChanged(_range->lower, _range->upper);
}

void GradientLineEdit::configureGradient()
{
    _gradient = new QCPColorGradient();
    _gradient->clearColorStops();
    _gradient->setColorStopAt(0, QColor("#0000ff"));
    _gradient->setColorStopAt(0.9, QColor("#ff6600"));
    _gradient->setColorStopAt(1, QColor("#ff0000"));

}

void GradientLineEdit::setMinMax(double min, double max)
{
    if (!_range)
    {
        qWarning() << EL_FORMAT_ERR("Range is not configured");
        return;
    }

    _range->lower = min;
    _range->upper = max;

    display(previousValue);

    //FIXME tima45
    //emit rangeChanged(_range->lower, _range->upper);
}

void GradientLineEdit::setRange(QCPRange *range, bool deleteOld)
{
    if (deleteOld && _range)
        delete _range;

    _range = range;
}

void GradientLineEdit::setGradient(QCPColorGradient *gradient, bool deleteOld)
{
    if (deleteOld && _gradient)
        delete _gradient;

    _gradient = gradient;
}

double GradientLineEdit::min()
{
    if (!_range)
    {
        qWarning() << EL_FORMAT_ERR("Range is not configured");
        return 0;
    }

    return _range->lower;
}

double GradientLineEdit::max()
{
    if (!_range)
    {
        qWarning() << EL_FORMAT_ERR("Range is not configured");
        return 0;
    }

    return _range->upper;
}

void GradientLineEdit::display(double value)
{
    previousValue = value;
    if (!_gradient || !_range)
    {
        qWarning() << EL_FORMAT_ERR("Gradient or range is not configured");
        return;
    }

    auto css = QString("background: %1; color: #FFFFFF").arg(QColor(_gradient->color(value, *_range)).name());
    auto text = QString("%1").arg(value, 0, 'f', 2, '0');
    setText(text);
    setStyleSheet(css);
}
