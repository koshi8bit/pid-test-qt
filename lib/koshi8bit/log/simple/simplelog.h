#ifndef SIMPLELOG_H
#define SIMPLELOG_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QString>

#include <lib/koshi8bit/easyliving.h>

//#define sl2(p1) qDebug() << p1; sl << p1;
//#define sl simpleLog->stream << "\n" <<

using namespace std;

class SimpleLog : public QObject
{
    Q_OBJECT
public:
    explicit SimpleLog(QString path, bool append = false, QObject *parent = nullptr);
    ~SimpleLog();
	void setHeader(QString message);
    QTextStream stream;

    void append(QString message, bool critical = false);

private:
    QFile *file;
signals:

};

ostream& operator<<(ostream& os, const SimpleLog& sl);


#endif // SIMPLELOG_H
