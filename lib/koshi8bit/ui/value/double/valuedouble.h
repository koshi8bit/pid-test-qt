#ifndef VALUEDOUBLE_H
#define VALUEDOUBLE_H

#include <QWidget>
#include <QLineEdit>

#include <lib/koshi8bit/easyliving.h>
#include <lib/koshi8bit/log/channeldouble.h>

namespace Ui {
class ValueDouble;
}

class ValueDouble : public QWidget
{
    Q_OBJECT

public:
    explicit ValueDouble(QWidget *parent = nullptr);
    ~ValueDouble() override;

    void configure(QString name, QString postfix, int precision = 3, bool hideSetWidget = true, bool scientificNotation = false, int fontSize = 10);
    void configure(ChannelDouble *getChannel, int fontSize = 10);
    void configure(ChannelDouble *getChannel, ChannelDouble *setChannel, int fontSize = 10);
    void setRangeSetter(double min, double max);

    QString name() const;
    void setName(const QString &name);

    int precision() const;
    void setPrecision(int precision);

    bool scientificNotation() const;
    void setScientificNotation(bool scientificNotation);

    double value() const;

    void setFontSize(int newValue);

    QLineEdit *widgetGet();
    QDoubleSpinBox *widgetSet();
    QLabel *labelLeftSpacer(), *labelNameAndPostfix();
    QPushButton *pushButton(); //TODO refactor to getter and setter /// delete me

    const static QString getWidgetBackgroundColor, getWidgetConnectedColor, getWidgetNotConnectedColor;

    QString postfix() const;
    void setPostfix(const QString &postfix);

    void syncAligment(ValueDouble *biggestLabelSample, ValueDouble *biggestValueSample, ValueDouble *sampleWidgetSet = nullptr, bool syncValueGet=true);
    void showOnlyValueGet(bool newValue);
    
    void setMaxDigitCount(int beforeDotCount);
    void setMaxDigitCount(int beforeDotCount, int afterDotCount);

    QString toolTipp() const;
    void setToolTipp(const QString &newToolTipp);



    bool connectedGetter() const;
    void setConnectedGetter(bool connected);

    bool connectedSetter() const;
    void setConnectedSetter(bool connected);

    void setModuleNames(QString moduleNameGetter, QString moduleNameSetter="<not set>");

private:
    int _precision;
    bool _scientificNotation, _connectedGetter, _connectedSetter;
    double _value;
    QString _name;
    QString _postfix;
    QString _toolTipp, _moduleNameGetter="<not set>", _moduleNameSetter="<not set>";
    Ui::ValueDouble *ui;
    void _setFontSize(QWidget *widget, int newValue);
    QColor color;

    void setColor(QWidget *widget, QString newColor);
    
signals:
    void valueChanged(double value);
    void valueConfirmed(double value);
    void valueCopyedToClipboard(QString newValue, QString message);
    void colorChanged(QColor newColor);

public slots:
    void setValue(double newValue);
    void setColor(QColor color);

private slots:
    void on_pushButtonSet_clicked();

    void on_pushButtonColor_clicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // VALUEDOUBLE_H
