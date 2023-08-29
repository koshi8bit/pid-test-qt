#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QColor>
#include <QDebug>

class Channel : public QObject
{
    Q_OBJECT
public:
    static QString pathJoin(QStringList &path);

    //TODO move to dir ./channel
    explicit Channel(QString name, QString postfix, QObject *parent = nullptr);
    explicit Channel(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);

    virtual ~Channel();


    QString logName() const;
    QString plotName() const;
    void setPlotName(const QString plotName);
    QString widgetName() const;
    void setWidgetName(const QString widgetName);

    QColor color() const;
    void setColor(const QColor &color);
    QString postfix() const;
    void setPostfix(const QString &postfix);


    const static QString seporator;

private:
    explicit Channel(QString plotName, QString widgetName, QString postfix, QObject *parent = nullptr);

    QString _plotName;
    QString _widgetName;
    QString _logName;
    QString _postfix;
    QColor _color;

protected:
    void setLogName(const QString logName);

    void _errorOccurred(QString message);


signals:
    void valueChanged();
    void valueChangedByNet();
    void errorOccurred(QString message);

    void valueChangedDouble(double newValue);
    void valueChangedBool(bool newValue);

public slots:
};

#endif // CHANNEL_H
