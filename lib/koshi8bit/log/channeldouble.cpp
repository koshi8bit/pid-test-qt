#include "channeldouble.h"

ChannelDouble::ChannelDouble(QString name, QString postfix, QObject *parent)
    :ChannelRealTimeGraph<double>(name, postfix, parent)
{
    configure();
}

ChannelDouble::ChannelDouble(QString name, QString postfix, QStringList &path, QObject *parent)
    :ChannelRealTimeGraph<double>(name, postfix, path, parent)
{
    configure();
}

ChannelDouble::ChannelDouble(QString sharedVariableName, QObject *parent)
    :ChannelRealTimeGraph<double>(sharedVariableName, parent)
{
    configure();
}

ChannelDouble::~ChannelDouble()
{
}


void ChannelDouble::setRawValue(double newRawValue)
{
    if (toScaledFunc == nullptr)
    {
        _errorOccurred(EL_FORMAT_ERR(QString("fromRawScaleFunc == nullptr at channel '%1'").arg(logName())));
        return;
    }
    setValue(toScaledFunc(newRawValue));
}

void ChannelDouble::setToScaledFunc(std::function<double(double)> f)
{
    toScaledFunc = f;
}

void ChannelDouble::setScaling(double minValue, double maxValue, double minRaw, double maxRaw)
{
    this->scalingMinValue = minValue;
    this->scalingMaxValue = maxValue;
    this->scalingMinRaw = minRaw;
    this->scalingMaxRaw = maxRaw;

    setToScaledFunc([this](double raw)
    {
        return (raw - this->scalingMinRaw) / (this->scalingMaxRaw - this->scalingMinRaw) *
                (this->scalingMaxValue - this->scalingMinValue) + this->scalingMinValue;
    });

    setToRawFunc([this](double scaled)
    {
        return (scaled - this->scalingMinValue) / (this->scalingMaxValue - this->scalingMinValue) *
                (this->scalingMaxRaw - this->scalingMinRaw) + this->scalingMinRaw;
    });
}

void ChannelDouble::setToRawFunc(std::function<double(double)> f)
{
    toRawFunc = f;
}

double ChannelDouble::rawValue()
{
    //FIXME DRY
    if (toRawFunc == nullptr)
    {
        _errorOccurred(EL_FORMAT_ERR(QString("toRawFunc == nullptr at channel '%1'").arg(logName())));
        return 0;
    }

    return _rawValue;
}

double ChannelDouble::calcAvg(AvgFunc func, double *error)
{
    if (!isCalcAvgEnabled())
        _avg = 0;

    if (func == AvgFunc::ArithmeticMean)
        _avg = calcArithmeticMean();

    if (func == AvgFunc::StandardDeviation)
    {
        _avg = calcStandardDeviation();
    }

    if (error)
        *error = _avgError;

    return _avg;
}

double ChannelDouble::avg()
{
    return _avg;
}

double ChannelDouble::avgError()
{
    return _avgError;
}

bool ChannelDouble::isCalcAvgEnabled()
{
    return avgBufferMaxSize() >= 2;
}

double ChannelDouble::calcArithmeticMean()
{
    auto result = 0.0;
    foreach(auto element, avgBuffer)
    {
        result += element;
    }
    result /= avgBuffer.count();
    return result;
}

double ChannelDouble::calcStandardDeviation()
{
    double avarage_mu = calcArithmeticMean();

    double summ=0;
    foreach(auto element, avgBuffer)
    {
        summ += qPow(element - avarage_mu, 2);
    }
    auto sigma_pow_2 = summ/(avgBuffer.count() - 1); // -1 is not bug, watch here https://ru.wikipedia.org/wiki/%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%BA%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5_%D0%BE%D1%82%D0%BA%D0%BB%D0%BE%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5#%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80_%D0%B2%D1%8B%D1%87%D0%B8%D1%81%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F_%D1%81%D1%82%D0%B0%D0%BD%D0%B4%D0%B0%D1%80%D1%82%D0%BD%D0%BE%D0%B3%D0%BE_%D0%BE%D1%82%D0%BA%D0%BB%D0%BE%D0%BD%D0%B5%D0%BD%D0%B8%D1%8F_%D0%BE%D1%86%D0%B5%D0%BD%D0%BE%D0%BA_%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D0%BA%D0%BE%D0%B2
    _avgError = qSqrt(sigma_pow_2);

    return avarage_mu;
}

int ChannelDouble::avgBufferMaxSize() const
{
    return _avgBufferMaxSize;
}

void ChannelDouble::setAvgBufferMaxSize(int bufferSize)
{
    _avgBufferMaxSize = bufferSize;
}

void ChannelDouble::setRange(double min, double max)
{
    _rangeMin = min;
    _rangeMax = max;
    setRangeEnable(true); //TODO DELETE ME
}

void ChannelDouble::setRangeEnable(bool rangeEnable)
{
    this->rangeEnable = rangeEnable;
    if (rangeEnable)
    {
        auto current = inRange();

        emit inRangeChanged(current);
        emit inRangeChangedInverted(!current);

        inRangePrev = current;
    }
    else
    {
        emit inRangeChanged(true);
        emit inRangeChangedInverted(false);
    }
}

bool ChannelDouble::inRange()
{
    return EasyLiving::isBetween(value(), _rangeMin, _rangeMax);
}

bool ChannelDouble::addToBufferOnEveryChange() const
{
    return _addToBufferOnEveryChange;
}

void ChannelDouble::setAddToBufferOnEveryChange(bool addToBufferOnEveryChange)
{
    _addToBufferOnEveryChange = addToBufferOnEveryChange;
}

void ChannelDouble::appendToAvgBuffer()
{
    avgBuffer.push_back(value());
    if (avgBuffer.size() > _avgBufferMaxSize)
        avgBuffer.pop_front();
}

void ChannelDouble::clearAvgBuffer()
{
    avgBuffer.clear();
}

int ChannelDouble::avgBufferSize()
{
    return avgBuffer.size();
}

double ChannelDouble::rangeMin() const
{
    return _rangeMin;
}

double ChannelDouble::rangeMax() const
{
    return _rangeMax;
}

void ChannelDouble::configure()
{
    connect(this, &Channel::valueChanged, [this]() { emit valueChangedDouble(value()); } );
    setScientificNotation(false);
    setPrecision(3);
}

void ChannelDouble::valueSetChild()
{
    if (rangeEnable)
    {
        auto current = inRange();

        if (current != inRangePrev)
        {
            emit inRangeChanged(current);
            emit inRangeChangedInverted(!current);
        }

        inRangePrev = current;
    }

    if (addToBufferOnEveryChange() & isCalcAvgEnabled())
    {
        appendToAvgBuffer();
    }

    if (toRawFunc != nullptr) { _rawValue = toRawFunc(value()); }

    if (realTimeGraph() != nullptr) { realTimeGraph()->addData(RealTimePlot::currentDateTime(), this->value()); }
}
