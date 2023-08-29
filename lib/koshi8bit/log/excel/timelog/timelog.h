#ifndef TIMELOG_H
#define TIMELOG_H

#include <QDateTime>

#include <lib/koshi8bit/log/excel/excel.h>
#include <lib/koshi8bit/easyliving.h>


class TimeLog : public Excel
{
public:
    TimeLog();

protected:
    QString headersPrefix() override;
    QString commitPrefix() override;

};

#endif // TIMELOG_H
