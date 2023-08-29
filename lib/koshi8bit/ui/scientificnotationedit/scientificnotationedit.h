#ifndef SCIENTIFICNOTATIONEDIT_H
#define SCIENTIFICNOTATIONEDIT_H

#include <QLineEdit>
#include <QValidator>
#include <QDoubleValidator>
#include <QLocale>
#include <QDebug>
#include <QRegularExpression>

class ScientificNotationEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ScientificNotationEdit(QWidget *parent = nullptr);

    void setValue(double value);
    double value();

private:
    QRegularExpressionValidator  *validator;
    double _value;

private slots:
    void changed();

signals:
    void valueChanged(double value);

};

#endif // SCIENTIFICNOTATIONEDIT_H
