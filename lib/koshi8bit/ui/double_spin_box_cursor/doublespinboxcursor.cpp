
#include "doublespinboxcursor.h"


DoubleSpinBoxCursor::DoubleSpinBoxCursor(QWidget *parent)
    :QDoubleSpinBox(parent)
{
//    setMinimum(-99);
//    setMaximum(99);
}

void DoubleSpinBoxCursor::stepBy(int steps)
{
    const int textLen = lineEdit()->text().length();
    const int cursorPos = qMax(lineEdit()->cursorPosition(), 1);
    auto kek = textLen - cursorPos - decimals();
    //qDebug() << kek;

    if (decimals() > 0) {
        if (kek == 0) {
            //return;
            kek = -1;
        }

        if (kek > 0) {
            kek--;
        }
    }

    auto delta = pow(10, kek)*steps;
    setValue(value() + delta);
    cursorPosPrev = cursorPos - textLen + lineEdit()->text().length();
    lineEdit()->setCursorPosition(cursorPosPrev);
}

void DoubleSpinBoxCursor::confirmValue()
{
    valueConfirmedPrev = value();
}

void DoubleSpinBoxCursor::keyPressEvent(QKeyEvent *event)
{
    auto key = event->key();
    //qDebug() << key << QString("0x%1").arg(key, 8, 16, QLatin1Char( '0' ));
    auto isEnter = (key == Qt::Key_Return) || ((key == Qt::Key_Enter));
    if (isEnter) {
        //qDebug() << "enter";
        emit valueConfirmed(value());
        confirmValue();
    }

    if ((event->matches(QKeySequence::Undo)) || (key == Qt::Key_Escape)) {
        //qDebug() << "ctrl+z or escape";
        setValue(valueConfirmedPrev);
    }

    QDoubleSpinBox::keyPressEvent(event);
    if (isEnter) {
        lineEdit()->setCursorPosition(cursorPosPrev);
    }
}

