#ifndef QLABELEXT_H
#define QLABELEXT_H

#include <QWidget>
#include <QLabel>

class QLabelExt : public QLabel
{
    Q_OBJECT
public:
    explicit QLabelExt(QWidget *parent = nullptr);

signals:
    void mouseDoubleClick(QMouseEvent *event);


    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // QLABELEXT_H
