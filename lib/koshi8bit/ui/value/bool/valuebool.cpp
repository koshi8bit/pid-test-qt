#include "valuebool.h"
#include "ui_valuebool.h"

ValueBool::ValueBool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueBool)
{
    ui->setupUi(this);
}

ValueBool::~ValueBool()
{
    delete ui;
}

void ValueBool::configure(QString name, QString trueText, QString falseText, QString moduleName, bool readOnly, QString toolTip)
{
    connect(ui->checkBox, &QCheckBox::toggled,
            this, &ValueBool::toggled);
    disconnectedText = QString("%1: Нет связи️").arg(name);
    disconnectedToolTipText = QString("%1 c '%2'").arg(disconnectedText).arg(moduleName);
    disconnectedText += "⚠";
    this->name = name;
    this->trueText = trueText;
    this->falseText = falseText;
    this->readOnly = readOnly;
    this->toolTip = toolTip;
    ui->label->setText(currentText());

    if (readOnly) {
        ui->checkBox->setEnabled(false);
    }

    connect(ui->checkBox, &QCheckBox::toggled, [this](bool checked){
        Q_UNUSED(checked)
        if (connected()) {
            ui->label->setText(currentText());
        }
    });
    setConnected(false);
}

bool ValueBool::connected() const
{
    return _connected;
}

bool ValueBool::checked() const
{
    return ui->checkBox->isChecked();
}

void ValueBool::setConnected(bool connected)
{
    if (_connectedPrevState == connected) {
        return;
    }


    _connected = connected;
    if (!readOnly) {
        ui->checkBox->setEnabled(connected);
        if (connected) {
            connect(ui->label, &ClickableLabel::clicked,
                    ui->checkBox, &QCheckBox::toggle);
        } else {
            disconnect(ui->label, &ClickableLabel::clicked,
                       ui->checkBox, &QCheckBox::toggle);
        }

    }

    if (connected) {
        ui->label->setText(currentText());
        setToolTip(toolTip);
    } else {
        ui->label->setText(disconnectedText);
        setToolTip(disconnectedToolTipText);
    }
    _connectedPrevState = connected;
}

void ValueBool::setChecked(bool checked)
{
    ui->checkBox->setChecked(checked);
}

QString ValueBool::currentText()
{
    return QString("%1: %2")
        .arg(name)
        .arg(ui->checkBox->isChecked() ? trueText : falseText);
}
