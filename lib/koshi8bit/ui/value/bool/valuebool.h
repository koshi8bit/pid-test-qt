#ifndef VALUEBOOL_H
#define VALUEBOOL_H

#include <QWidget>

namespace Ui {
class ValueBool;
}

class ValueBool : public QWidget
{
    Q_OBJECT

public:
    explicit ValueBool(QWidget *parent = nullptr);
    ~ValueBool();

    void configure(QString name, QString trueText, QString falseText, QString moduleName, bool readOnly, QString toolTip = "");
    bool connected() const;
    bool checked() const;

public slots:
    void setConnected(bool connected);
    void setChecked(bool checked);

signals:
    void toggled(bool checked);

private:
    Ui::ValueBool *ui;
    bool _connected, _connectedPrevState=true;
    QString disconnectedText, disconnectedToolTipText, toolTip, trueText, falseText, name;
    QString currentText();
    bool readOnly;
};

#endif // VALUEBOOL_H
