#ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H

#include <QObject>
#include <QColor>
#include <lib/koshi8bit/ui/qcustomplot/qcustomplot.h>

#include "graphlegenditem.h"

class AbstractGraph : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGraph(const QString &label, const QString &postfix, QColor color,
                           QCustomPlot *qcp = nullptr, int precision = 3,
                           bool scientificNotation = false);
    virtual ~AbstractGraph();

    QString label() const;
    QString postfix() const;
    QColor color() const;
    bool visible() const;
    bool scientificNotation() const;
    int precision() const;
    QCustomPlot *qcp();

    GraphLegendItem *legendItem();

signals:
    void visibleChanged(bool newValue);
    void colorChanged(QColor newValue);

private slots:
    void setVisibleByWidget(bool newValue);
    void setColorByWidget(QColor newValue);

public slots:
    void setVisible(bool newValue);
    void setColor(QColor newValue);

private:
    QString _label;
    QString _postfix;
    QColor _color;
    bool _visible;
    bool _scientificNotation;
    int _precision;
    QCustomPlot *_qcp;

    void _setVisible(bool newValue);
    void _setColor(QColor newValue);

protected:
    GraphLegendItem *_legendItem;

    virtual void updateLegendItem() = 0;
    virtual void abstractSetVisible() = 0;
    virtual void abstractSetColor() = 0;

};


#endif // ABSTRACTGRAPH_H
