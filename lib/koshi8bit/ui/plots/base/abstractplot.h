#ifndef ABSTRACTPLOT_H
#define ABSTRACTPLOT_H

#include <QWidget>
#include <lib/koshi8bit/ui/qcustomplot/qcustomplot.h>

#include <lib/koshi8bit/ui/printscreener/printscreener.h>
//#include <lib/koshi8bit/log/channeldouble.h>

#include "abstractgraph.h"
#include "colorsetter.h"
#include "axisvalueconfig.h"

namespace Ui {
class AbstractPlot;
}

class AbstractPlot : public QWidget
{
    Q_OBJECT

public:
    static void autoScaleAxis(QCPAxis *axis);
    explicit AbstractPlot(QWidget *parent = nullptr);
    ~AbstractPlot();

    QVector<AbstractGraph *> graphs();
    void addAbstractGraph(AbstractGraph *graph);

    void setLegendVisible(bool visible);
    void setSplitterWidth(int widthL, int widthR, AbstractPlot *senderWidget);
    void setSplitterWidth(int widthR);


signals:
    void splitterWidthChanged(int widthL, int widthR);

public slots:
    void setSplitterWidth(int widthL, int widthR);



//#define graphCast(element, type) static_cast<type>(element)
//    template < template <typename> class BinPred , typename T >
//    QVector<T*> foo()
//    {
//        QVector<T*> result;
//        foreach(auto element, graphs())
//        {
//            result.append(static_cast<T*>(element));
//        }
//        return result;
//    }

    QCustomPlot *qcp();

    //TODO delete method
    //void configureAxis(bool yAxis2, const QString &label, const QString &postfix = "", double min=0, double max=100, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);
    //void configureAxis(QCPAxis *axis, ChannelDouble *channel, double min=0, double max=100);
    void configureAxis(QCPAxis *axis, const QString &label, const QString &postfix = "", double min=0, double max=100, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear, QColor color=Qt::white);


private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void on_pushButtonPrintScreen_clicked();

    void on_pushButtonHelp_clicked();

    void on_pushButtonOptions_toggled(bool checked);

    void on_pushButtonPrintScreenCopy_clicked();

    void on_pushButtonPrintScreenPaint_clicked();

    void _splitterMoved(int pos, int index);



private:
    Ui::AbstractPlot *ui;
    void configureLegend();

    void setButtonsVisible(bool visible, bool options);

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);
    void _setSplitterWidth(int widthL, int widthR);

protected:
    ColorSetter colorSetter;

    void configurePlotBackground(bool excelStyle);
    void configurePlotBackgroundAxis(QCPAxis *axis, bool excelStyle, QColor color=Qt::white);


    virtual void abstractAxisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);


    QCustomPlot *_qcp;
    QVBoxLayout *_legendLayout;
    QVector<AbstractGraph *> _graphs;


};

#endif // ABSTRACTPLOT_H
