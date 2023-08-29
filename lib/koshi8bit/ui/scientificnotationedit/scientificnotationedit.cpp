#include "scientificnotationedit.h"

ScientificNotationEdit::ScientificNotationEdit(QWidget *parent)
    : QLineEdit (parent)
{
    //FIXME 0,99 не работает, не вводится, когда пустое поле
//    auto validator = new QDoubleValidator(-9999999999.0, 999999999.0, 2, parent);
//    validator->setNotation(QDoubleValidator::Notation::ScientificNotation);
    validator = new QRegularExpressionValidator(QRegularExpression(R"([+\-]?(?:0|[1-9]\d*)(?:\.\d*|\,\d*)?(?:[eE][+\-]?\d+)?)"));
    this->setValidator(validator);

    connect(this, &QLineEdit::editingFinished,
            this, &ScientificNotationEdit::changed);
}

void ScientificNotationEdit::setValue(double value)
{
    _value = value;
    //TODO EasyLiving::formatDouble()
    auto textValue = QString("%1").arg(value, 0, 'e', 3, '0').replace('.', ',');
    setText(textValue);
    emit valueChanged(value);
}

double ScientificNotationEdit::value()
{
    return _value;
//    bool ok;
//    QLocale locate(QLocale::Russian, QLocale::Russia);
//    auto text = this->text();
//    auto result = locate.toDouble(text, &ok);
//    if (!ok)
//    {
//        qDebug() << "ScientificNotationEdit: value parse error";
//        return 0;
//    }
    //    return result;
}

void ScientificNotationEdit::changed()
{
    bool ok;
    QLocale locate(QLocale::Russian, QLocale::Russia);
    auto text = this->text();
    auto result = locate.toDouble(text, &ok);
    if (!ok)
    {
        qWarning() << "ScientificNotationEdit: value parse error";
        return;
    }
    emit valueChanged(result);
}
