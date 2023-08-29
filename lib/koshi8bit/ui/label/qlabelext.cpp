#include "qlabelext.h"

QLabelExt::QLabelExt(QWidget *parent) : QLabel(parent)
{

}

void QLabelExt::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit mouseDoubleClick(event);
    QLabel::mouseDoubleClickEvent(event);
}
