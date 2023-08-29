#include "faultswidget.h"

FaultsWidget::FaultsWidget(QScrollArea *widget) : QWidget(widget)
{
    if (widget != nullptr)
        layoutFaults = new QVBoxLayout(widget->widget());
    else
        layoutFaults = new QVBoxLayout();

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layoutFaults->addItem(spacer);

    _template = EasyLiving::readFile(":/faults/ui/faults/template.html");
}

void FaultsWidget::addFault(Fault *fault)
{
    layoutFaults->insertWidget(layoutFaults->count()-1, fault->widget());
    _faults.append(fault);

    connect(fault, &Fault::visibleChanged, [this](bool visible) {
        Q_UNUSED(visible)
        triggerFaults(faults());
    });
}

void FaultsWidget::configureBorder(QLabel *top, QLabel *left, QLabel *right, QLabel *bottom)
{
    border.append(top);
    border.append(left);
    border.append(right);
    border.append(bottom);

    borderMessage.append(top);
    borderMessage.append(bottom);

    foreach(auto lbl, border)
    {
        lbl->setText("  ");
        lbl->setStyleSheet("background-color: red; color: yellow;");
    }

//    foreach(auto lbl, borderMessage)
//    {
//        lbl->setText(borderMessageText);
//    }

    hideFaultBorder();
}

void FaultsWidget::showFaultBorder(QString str)
{
    _isFaultTriggered = true;
    auto tooltip = _template.arg(str);

    foreach(auto lbl, border)
    {
        lbl->setVisible(true);
        lbl->setToolTip(tooltip);
    }

    auto shortMessage = str.split(joiner).join("; "); //TODO убрать замену каждый раз. Передавать в функцию стринглист и только для тултипа делать джоин <br/>

    foreach(auto lbl, borderMessage)
    {
        lbl->setText(borderMessageText + " " + shortMessage);
    }
}

void FaultsWidget::hideFaultBorder()
{
    _isFaultTriggered = false;
    foreach(auto lbl, border)
    {
        lbl->setVisible(false);
    }
}

QString FaultsWidget::faults()
{
    QStringList result;
    foreach(auto elemnt, _faults)
    {
        if (elemnt->isVisible())
        {
            result.append(elemnt->message());
        }
    }
    return result.join(joiner);
}

bool FaultsWidget::isFaultTriggered() const
{
    return _isFaultTriggered;
}

void FaultsWidget::triggerFaults(QString faults)
{
    if (faults.isEmpty())
    {
        hideFaultBorder();

        emit faultTriggered(false, faults);
    }
    else
    {
        showFaultBorder(faults);

        emit faultTriggered(true, faults);
    }


}
