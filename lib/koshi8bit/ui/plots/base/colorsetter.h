#ifndef COLORSETTER_H
#define COLORSETTER_H

#include <QObject>
#include <QStack>
#include <QQueue>
#include <QColor>
#include <QtDebug>
#include <QRandomGenerator>

#include <lib/koshi8bit/easyliving.h>

class ColorSetter : public QObject
{
    Q_OBJECT
public:
    explicit ColorSetter(QObject *parent = nullptr);

    QColor getColor(bool random=false);
    void resetColors();

private:
    QList<QColor> *colors;
    int currentIndex = 0;

signals:

public slots:
};

#endif // COLORSETTER_H
