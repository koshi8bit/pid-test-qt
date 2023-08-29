#include "timelog.h"

TimeLog::TimeLog()
    : Excel()

{

}

QString TimeLog::headersPrefix()
{
    QString date;
    QString dateFull;

    date = "Время";
    dateFull = "Полная дата";

    return QString("%1%2%3%4")
            .arg(date)
            .arg(elementDelimeter)
            .arg(dateFull)
            .arg(elementDelimeter);
}

QString TimeLog::commitPrefix()
{
    auto dt = QDateTime::currentDateTime();
    return QString("%1%2%3%4")
            .arg(dt.toString(EasyLiving::formatTimeUi(false)))
            .arg(elementDelimeter)
            .arg(dt.toString(EasyLiving::formatDateTimeUi(true)))
            .arg(elementDelimeter);
}
