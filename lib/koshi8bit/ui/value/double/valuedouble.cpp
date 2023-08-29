#include "valuedouble.h"
#include "ui_valuedouble.h"

const QString ValueDouble::getWidgetBackgroundColor = "#E1E1E1";


ValueDouble::ValueDouble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueDouble)
{
    ui->setupUi(this);
    ui->pushButtonColor->setVisible(false);
    ui->lineEditValueGet->setReadOnly(true);

    ui->lineEditValueGet->setStyleSheet(QString("background-color: %1;")
                                                .arg(getWidgetBackgroundColor));

    ui->doubleSpinBoxValueSet->setAlignment(Qt::AlignRight);
    auto font1 = ui->doubleSpinBoxValueSet->font();
    font1.setFamily(QString::fromUtf8("Consolas"));
    ui->doubleSpinBoxValueSet->setFont(font1);


    //ui->labelLeftSpacer->setStyleSheet(QString("background-color: %1").arg(getWidgetColor));
    //this->setToolTip("<html><head/><body><p>Двойное нажатие копирует значение в буфер обмена</p></body></html>");
    //connect(ui->doubleSpinBoxValueSet, SIGNAL(valueChanged(double)), this, SIGNAL(valueChanged(double)));
}

ValueDouble::~ValueDouble()
{
    delete ui;
}


void ValueDouble::configure(QString name, QString postfix, int precision, bool hideSetWidget, bool scientificNotation, int fontSize)
{
    setPostfix(postfix);
    setName(name);
    setPrecision(precision);

    ui->doubleSpinBoxValueSet->setDecimals(this->precision());

    ui->doubleSpinBoxValueSet->setVisible(!hideSetWidget);
    ui->pushButtonSet->setVisible(!hideSetWidget);
    //ui->labelLeftSpacer->setVisible(hideSetWidget);

    setScientificNotation(scientificNotation);
    setFontSize(fontSize);
    setValue(0);
    setColor(QColor(240, 240, 240));

    connect(ui->doubleSpinBoxValueSet, SIGNAL(valueChanged(double)),
            this, SIGNAL(valueChanged(double)));
    connect(ui->doubleSpinBoxValueSet, &DoubleSpinBoxCursor::valueConfirmed,
            this, &ValueDouble::valueConfirmed);
}

void ValueDouble::configure(ChannelDouble *getChannel, int fontSize)
{
    connect(getChannel, &ChannelDouble::valueChangedDouble,
            this, &ValueDouble::setValue, Qt::QueuedConnection);
    configure(getChannel->widgetName(), getChannel->postfix(), getChannel->precisionWidget(),
              true, getChannel->scientificNotation(), fontSize);
}

void ValueDouble::configure(ChannelDouble *getChannel, ChannelDouble *setChannel, int fontSize)
{
    connect(getChannel, &ChannelDouble::valueChangedDouble,
            this, &ValueDouble::setValue, Qt::QueuedConnection);
    connect(this, &ValueDouble::valueConfirmed,
            setChannel, &ChannelDouble::setValue, Qt::QueuedConnection);
    configure(getChannel->widgetName(), getChannel->postfix(), getChannel->precisionWidget(),
              false, getChannel->scientificNotation(), fontSize);
}


void ValueDouble::setFontSize(int newValue)
{
    _setFontSize(ui->labelNameAndPostfix, newValue);
    _setFontSize(ui->lineEditValueGet, newValue);
    _setFontSize(ui->doubleSpinBoxValueSet, newValue);
    _setFontSize(ui->pushButtonSet, newValue);

//    if (newValue == 30)
//    {
//        this->setMinimumHeight(71);
//    }

    if (newValue == 25)
    {
        this->setMinimumHeight(44);
    }

//    if (newValue == 14)
//    {
//        this->setMinimumHeight(36);
//    }

//    if (newValue == 8)
//    {
//        this->setMinimumHeight(38);
//    }
}

void ValueDouble::setMaxDigitCount(int beforeDotCount)
{
    setMaxDigitCount(beforeDotCount, precision());
}

void ValueDouble::setMaxDigitCount(int beforeDotCount, int afterDotCount)
{
    if (beforeDotCount <= 0) {
        qDebug() << EL_FORMAT_ERR("Invalid arg: beforeDotCount");
        return;
    }
    if (afterDotCount < 0) {
        qDebug() << EL_FORMAT_ERR("Invalid arg: afterDotCount");
        return;
    }

    QString str = "-⚠️";
    if (scientificNotation()) {
        auto value = pow(10, beforeDotCount-1) + pow(10, -afterDotCount);
        str += EasyLiving::formatDouble(value, afterDotCount, scientificNotation(), false, EasyLiving::Point);
    } else {
        for (int i=0; i<beforeDotCount; i++) {
            str += "1";
        }
        if (afterDotCount != 0) {
            str += ".";
        }
        for (int i=0; i<afterDotCount; i++) {
            str += "1";
        }
    }

    QFontMetrics fm(ui->lineEditValueGet->font());
    auto maxWidth = static_cast<int>(fm.horizontalAdvance(str))+10;
    ui->lineEditValueGet->setMaximumWidth(maxWidth);
}

QString ValueDouble::toolTipp() const
{
    return _toolTipp;
}

void ValueDouble::setToolTipp(const QString &newToolTipp)
{
    _toolTipp = newToolTipp;
    ui->labelNameAndPostfix->setToolTip(newToolTipp);
}

bool ValueDouble::connectedGetter() const
{
    return _connectedGetter;
}

void ValueDouble::setConnectedGetter(bool connected)
{
    _connectedGetter = connected;
    setValue(value());
    if (connected) {
        ui->lineEditValueGet->setToolTip("");
    } else {
        ui->lineEditValueGet->setToolTip(QString("Нет связи с '%1'")
                                             .arg(_moduleNameGetter));
    }
}

bool ValueDouble::connectedSetter() const
{
    return _connectedSetter;
}

void ValueDouble::setConnectedSetter(bool connected)
{
    _connectedSetter = connected;
    ui->doubleSpinBoxValueSet->setEnabled(connected);
    ui->pushButtonSet->setEnabled(connected);

    if (connected) {
        ui->doubleSpinBoxValueSet->setToolTip("");
        ui->pushButtonSet->setToolTip("");
    } else {
        auto text = QString("Нет связи с '%1'").arg(_moduleNameSetter);
        ui->doubleSpinBoxValueSet->setToolTip(text);
        ui->pushButtonSet->setToolTip(text);
    }
}

void ValueDouble::setModuleNames(QString moduleNameGetter, QString moduleNameSetter)
{
    _moduleNameGetter = moduleNameGetter;
    _moduleNameSetter = moduleNameSetter;

    setConnectedGetter(false);
    setConnectedSetter(false);
}

void ValueDouble::setRangeSetter(double min, double max)
{
    ui->doubleSpinBoxValueSet->setRange(min, max);
}

QLineEdit *ValueDouble::widgetGet()
{
    return ui->lineEditValueGet;
}

QDoubleSpinBox *ValueDouble::widgetSet()
{
    return ui->doubleSpinBoxValueSet;
}

QLabel *ValueDouble::labelLeftSpacer()
{
    return ui->labelLeftSpacer;
}

QLabel *ValueDouble::labelNameAndPostfix()
{
    return ui->labelNameAndPostfix;
}

QPushButton *ValueDouble::pushButton()
{
    return ui->pushButtonSet;
}

QString ValueDouble::postfix() const
{
    return _postfix;
}

void ValueDouble::setPostfix(const QString &postfix)
{
    _postfix = postfix;
}

void ValueDouble::syncAligment(ValueDouble *sampleWidgetLabel, ValueDouble *sampleWidgetGet, ValueDouble *sampleWidgetSet, bool syncValueGet)
{
    if (syncValueGet)
    {
        ui->lineEditValueGet->setMinimumWidth(sampleWidgetGet->widgetGet()->width());
    }

//    sampleWidgetLabel->labelLeftSpacer()->setVisible(false);
    auto thisSpacerWdth = sampleWidgetLabel->labelNameAndPostfix()->width() -
                          ui->labelNameAndPostfix->width() +
//                          this->layout()->spacing() - 12;
                            this->layout()->spacing() + 2;
    ui->labelLeftSpacer->setMinimumWidth(thisSpacerWdth);

    if (sampleWidgetSet) {
        ui->doubleSpinBoxValueSet->setMinimumWidth(sampleWidgetSet->widgetSet()->width());
    }
}


void ValueDouble::showOnlyValueGet(bool newValue)
{
    Q_UNUSED(newValue)

    ui->labelNameAndPostfix->setVisible(false);
    ui->doubleSpinBoxValueSet->setVisible(false);
    ui->pushButtonSet->setVisible(false);
}

double ValueDouble::value() const
{
    return _value;
}

QString ValueDouble::name() const
{
    return _name;
}

void ValueDouble::setName(const QString &name)
{
    auto text = QString("%1, %2").arg(name).arg(postfix());
    ui->labelNameAndPostfix->setText(text);
    _name = name;
}

bool ValueDouble::scientificNotation() const
{
    return _scientificNotation;
}

void ValueDouble::setScientificNotation(bool scientificNotation)
{
    _scientificNotation = scientificNotation;
}

int ValueDouble::precision() const
{
    return _precision;
}

void ValueDouble::setPrecision(int precision)
{
    _precision = precision;
}

void ValueDouble::setValue(double newValue)
{
    _value = newValue;
    auto str = EasyLiving::formatDouble(newValue, _precision, _scientificNotation);
    if (!connectedGetter()) {
        str += "⚠️";
    }
    ui->lineEditValueGet->setText(str);
}

void ValueDouble::setColor(QColor color)
{
    this->color = color;
    QString css = QString("background: %1;").arg(color.name());
    ui->pushButtonColor->setStyleSheet(css);
}

void ValueDouble::_setFontSize(QWidget *widget, int newValue)
{
    auto _font = widget->font();
    _font.setPointSize(newValue);
    widget->setFont(_font);
}

void ValueDouble::setColor(QWidget *widget, QString newColor)
{
    widget->setStyleSheet(QString("color: %1").arg(newColor));
}

void ValueDouble::on_pushButtonSet_clicked()
{
    emit valueConfirmed(ui->doubleSpinBoxValueSet->value());
    ui->doubleSpinBoxValueSet->confirmValue();
}

void ValueDouble::mouseDoubleClickEvent(QMouseEvent *event)
{
    QClipboard *clipboard = QApplication::clipboard();
    auto valueStr = EasyLiving::formatDouble(value(), _precision, _scientificNotation);

    clipboard->setText(valueStr);
    emit valueCopyedToClipboard(valueStr, QString("Значение '%1' скопировано в буфер обмена (%2)").arg(name()).arg(valueStr));

    QWidget::mouseDoubleClickEvent(event);

}


void ValueDouble::on_pushButtonColor_clicked()
{
    auto color = QColorDialog::getColor(this->color, this, tr("Выберите цвет"));
    if (color.isValid())
    {
        setColor(color);
        emit colorChanged(color);
    }
}

