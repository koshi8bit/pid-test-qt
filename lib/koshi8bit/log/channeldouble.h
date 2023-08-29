#ifndef CHANNELDOUBLE_H
#define CHANNELDOUBLE_H


#include "channelrealtimegraph.h"


class ChannelDouble : public ChannelRealTimeGraph<double>
{
    Q_OBJECT
public:
    enum AvgFunc{
        ArithmeticMean,
        StandardDeviation
        //Median,
    };
    Q_ENUM(AvgFunc)


    ChannelDouble(QString name, QString postfix, QObject *parent = nullptr);
    ChannelDouble(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);
    ChannelDouble(QString sharedVariableName, QObject *parent = nullptr);
    ~ChannelDouble() override;

    void setScaling(double scalingMinValue, double scalingMaxValue, double scalingMinRaw, double scalingMaxRaw);

    void setToScaledFunc(std::function<double(double)> f);
    void setRawValue(double newValue);

    void setToRawFunc(std::function<double(double)> f);
    double rawValue();


    double calcAvg(AvgFunc func = AvgFunc::ArithmeticMean, double *error = nullptr);
    double avg();
    double avgError();
    bool isCalcAvgEnabled();

    int avgBufferMaxSize() const;
    void setAvgBufferMaxSize(int bufferSize);

    void setRange(double min, double max);
    void setRangeEnable(bool emitSignal);
    bool inRange();

    bool addToBufferOnEveryChange() const;
    void setAddToBufferOnEveryChange(bool addToBufferOnEveryChange);

    void appendToAvgBuffer();
    void clearAvgBuffer();
    int avgBufferSize();

    double rangeMin() const;
    double rangeMax() const;

private:
    double _avg=0, _avgError=0;
    //double (*toScaledFunc)(double) = nullptr;
    std::function<double(double)> toScaledFunc = nullptr;

    double _rawValue;
    //double (*toRawFunc)(double) = nullptr;
    std::function<double(double)> toRawFunc = nullptr;
    double scalingMinValue=0, scalingMaxValue=0, scalingMinRaw=0, scalingMaxRaw=0;
    double _rangeMin=0, _rangeMax=0;
    bool rangeEnable = false, inRangePrev = true;

    //QQueue<double> buffer;
    QList<double> avgBuffer;
    int _avgBufferMaxSize = 0;
    bool _addToBufferOnEveryChange = false;


    void configure();

    double calcArithmeticMean();
    double calcStandardDeviation();

    
signals:
    //TODO: template fuck
    //void valueChangedDouble(double newValue);
    void inRangeChanged(bool inRange);
    void inRangeChangedInverted(bool notInRange);

protected:
    void valueSetChild() override;
private slots:
};

#endif // CHANNELDOUBLE_H
