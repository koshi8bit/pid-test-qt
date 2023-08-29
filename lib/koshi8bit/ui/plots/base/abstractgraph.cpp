#include "abstractgraph.h"

AbstractGraph::AbstractGraph(const QString &label, const QString &postfix, QColor color,
                             QCustomPlot *qcp, int precision, bool scientificNotation)
    :QObject(qcp)
{
    _label = label;
    _postfix = postfix;

    _color = color;
    _qcp = qcp;

    _precision = precision;
    _scientificNotation = scientificNotation;

    _visible = true;

    _legendItem = new GraphLegendItem(label, postfix, color, _precision, scientificNotation);
    connect(_legendItem, &GraphLegendItem::visibleChanged, this, &AbstractGraph::setVisibleByWidget);
    connect(_legendItem, &GraphLegendItem::colorChanged, this, &AbstractGraph::setColorByWidget);

}

AbstractGraph::~AbstractGraph()
{

}

GraphLegendItem *AbstractGraph::legendItem()
{
    return _legendItem;
}

void AbstractGraph::setVisibleByWidget(bool newValue)
{
    _setVisible(newValue);
    emit visibleChanged(newValue);
}

void AbstractGraph::setColorByWidget(QColor newValue)
{
    _setColor(newValue);
    emit colorChanged(newValue);
}

void AbstractGraph::setVisible(bool newValue)
{
    //TODO autoscale without unsivible graphs
    _setVisible(newValue);
    if (_legendItem)
        _legendItem->setVisibleValue(newValue);
}

void AbstractGraph::setColor(QColor newValue)
{
    _setColor(newValue);

    if (_legendItem)
        _legendItem->setColor(newValue);
}

QString AbstractGraph::label() const
{
    return _label;
}

QString AbstractGraph::postfix() const
{
    return _postfix;
}

bool AbstractGraph::scientificNotation() const
{
    return _scientificNotation;
}

int AbstractGraph::precision() const
{
    return _precision;
}

QColor AbstractGraph::color() const
{
    return _color;
}

QCustomPlot *AbstractGraph::qcp()
{
    return _qcp;
}

bool AbstractGraph::visible() const
{
    return _visible;
}

void AbstractGraph::_setVisible(bool newValue)
{
    _visible = newValue;
    abstractSetVisible();
    _qcp->replot();
}

void AbstractGraph::_setColor(QColor newValue)
{
    _color = newValue;
    abstractSetColor();
    _qcp->replot();
}
