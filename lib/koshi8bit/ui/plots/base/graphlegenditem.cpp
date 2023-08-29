#include "graphlegenditem.h"
#include "ui_graphlegenditem.h"

GraphLegendItem::GraphLegendItem(const QString &label, const QString &postfix, QColor color, int precision, bool scientificNotation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphLegendItem)
{
    ui->setupUi(this);
    this->label = label;
    this->postfix = postfix;
    setColor(color);
    this->precision = precision;
    ui->checkBoxVisible->setChecked(true);
    setLabelText(label);
    this->scientificNotation = scientificNotation;

}

void GraphLegendItem::setColor(QColor &color)
{
    this->color = color;
    QString css = QString("background: %1;").arg(color.name());
    ui->pushButtonColor->setStyleSheet(css);
}

GraphLegendItem::~GraphLegendItem()
{
    delete ui;
}

void GraphLegendItem::setValue(double value, bool showDelta, double avg)
{
    if (scientificNotation)
    {
        setValue(EasyLiving::formatDouble(value, precision, true), showDelta, avg);
    }
    else
    {
        setValue(EasyLiving::formatDouble(value, precision), showDelta, avg);
    }
}

void GraphLegendItem::setValue(const QString &value, bool showDelta, double avg)
{
    if (!visible)
    {
        ui->label->setText(label);
        return;
    }

//    auto _template = QString("%1: ") + (showDelta ? "Δ" : "") + "%2";

//    auto text = QString(_template)
//                       .arg(label)
//                       .arg(value);
    auto _template = QString(showDelta ? "Δ" : "");
//    auto _template = showDelta ? QString("Δ") : QString(", %1").arg(postfix);
//    auto _postfix = QString(!postfix.isEmpty() && visible ? "Δ" : "");
    auto _postfix = !postfix.isEmpty() && visible ? QString(", %1").arg(postfix) : QString("");
    QString text = "";
    if (avg == 0){
        _template += QString("%1%2 | %3");
        text = QString(_template)
                            .arg(value)
                            .arg(_postfix)
                            .arg(label);

    } else {
        _template += QString("%1%2 | %3 | %4");
        text = QString(_template)
                            .arg(value)
                            .arg(_postfix)
                            .arg(avg)
                            .arg(label);
    }



//    if (!postfix.isEmpty() && visible)
//    {
//        //text.append(" (" + postfix + ")");
//        text.append(" [" + postfix + "]");
//    }

    ui->label->setText(text);
}

void GraphLegendItem::setLabelText(const QString &string)
{
    ui->label->setText(string);
}

void GraphLegendItem::on_pushButtonColor_clicked()
{
    auto color = QColorDialog::getColor(this->color, this, tr("Выберите цвет"));
    if (color.isValid())
    {
        setColor(color);

        emit colorChanged(color);
    }

}

void GraphLegendItem::setVisibleValue(bool newValue)
{
    _setVisibleValue(newValue);
    ui->checkBoxVisible->setChecked(newValue);

}

void GraphLegendItem::on_checkBoxVisible_toggled(bool checked)
{
    _setVisibleValue(checked);
    emit visibleChanged(checked);
}

void GraphLegendItem::_setVisibleValue(bool newValue)
{
    visible = newValue;
    if (!newValue)
    {
        setValue("");
    }
}
