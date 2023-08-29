#ifndef GRAPHLEGENDITEM_H
#define GRAPHLEGENDITEM_H

#include <QWidget>
#include <QColorDialog>

//FIXME
#include <lib/koshi8bit/easyliving.h>


namespace Ui {
class GraphLegendItem;
}

class GraphLegendItem : public QWidget
{
    Q_OBJECT

public:
    explicit GraphLegendItem(const QString &label, const QString &postfix, QColor color, int precision = 3, bool scientificNotation = false, QWidget *parent = nullptr);
    ~GraphLegendItem();

    void setValue(double value, bool showDelta = false, double avg = 0);
    void setValue(const QString &value, bool showDelta = false, double avg = 0);
    void setLabelText(const QString &string);

public slots:
    void setVisibleValue(bool newValue);
    void setColor(QColor &color);

private slots:
    void on_pushButtonColor_clicked();

    void on_checkBoxVisible_toggled(bool checked);

signals:
    void visibleChanged(bool newValue);
    void colorChanged(QColor newColor);

private:
    Ui::GraphLegendItem *ui;
    QString label;
    QString postfix;
    QColor color;
    bool scientificNotation = false;
    int precision;
    bool visible = true;

    void _setVisibleValue(bool newValue);

};

#endif // GRAPHLEGENDITEM_H
