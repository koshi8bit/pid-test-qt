
#ifndef DOUBLESPINBOXCURSOR_H
#define DOUBLESPINBOXCURSOR_H

#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QDebug>
#include <QKeyEvent>
#include <QKeySequence>
#include <QApplication>
#include <cmath>



class DoubleSpinBoxCursor : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit DoubleSpinBoxCursor(QWidget *parent = nullptr);
    void stepBy(int steps) override;
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void confirmValue();

signals:
    void valueConfirmed(double value);

private:
    double valueConfirmedPrev = 0;
    int cursorPosPrev = 0;
};

#endif // DOUBLESPINBOXCURSOR_H
