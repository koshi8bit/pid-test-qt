#ifndef EXCEL_H
#define EXCEL_H

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>

#include <lib/koshi8bit/log/log.h>
#include <lib/koshi8bit/log/channelt.h>
#include <lib/koshi8bit/log/channeldouble.h>
#include <lib/koshi8bit/log/channelbool.h>
#include <lib/koshi8bit/log/channelqstring.h>
#include <lib/koshi8bit/easyliving.h>

#include "excelfile.h"


class Excel : public Log
{

public:
    enum HeaderModeFlag {
        NoHeader = 0x0000,
        PlotName = 0x0001,
        LogName = 0x0002,
        WidgetName = 0x0004
    };
    Q_DECLARE_FLAGS(HeaderMode, HeaderModeFlag)

    Excel(QObject *parent = nullptr);
    ~Excel();

    void configure(QString path, HeaderMode headerMode);

    void push() override;
    void commit() override;

    static const QString elementDelimeter;
    static const QString lineDelimeter;


protected:
    static QString formatDoubleValue(ChannelDouble *channel);

    HeaderMode headerMode;
    void finishConfigureChild() override;

    virtual QString headersPrefix() = 0;
    virtual QString commitPrefix() = 0;

private:
    ExcelFile *currentSession;
    ExcelFile *currentDay;

    void finalPush(ExcelFile *excelFile);
    void appendToBuffers(QString message, bool addToCurrentDay = true);

    void configureHeader();
    void generateHeaderLine(HeaderModeFlag flag);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Excel::HeaderMode)

#endif // EXCEL_H
