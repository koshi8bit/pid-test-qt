#include "excel.h"

const QString Excel::elementDelimeter = "\t";
const QString Excel::lineDelimeter = "\r\n";

//TODO clean from currentSession
Excel::Excel(QObject *parent)
    : Log(parent)
{

}

Excel::~Excel()
{
    delete currentSession;
    delete currentDay;

//    finalPush(currentSession);
//    finalPush(currentDay);
}

void Excel::configure(QString path, HeaderMode headerMode)
{
    auto _path = QDir(path);
    auto date = QDateTime::currentDateTime();

    currentDay = new ExcelFile(thread);
    connect(currentDay, &ExcelFile::errorOcurred, this, &Excel::errorOcurred);
    currentDay->configure(date, EasyLiving::formatDateFile(), _path.filePath(".days"), "Windows-1251");

    currentSession = new ExcelFile(thread);
    connect(currentSession, &ExcelFile::errorOcurred, this, &Excel::errorOcurred);
    currentSession->configure(date, EasyLiving::formatDateTimeFile(), _path.filePath(".sessions"), "Windows-1251");

    this->headerMode = headerMode;
}

//void Excel::finalPush(ExcelFile *excelFile)
//{
//    if (excelFile->push())
//    {
//        delete excelFile;
//    }
//    else
//    {
//        emit errorOcurred(KB4_FORMAT_ERR(QString("Final push failed <%1>").arg(excelFile->fileName())));
//    }
//}

void Excel::appendToBuffers(QString message, bool addToCurrentDay)
{
    currentSession->append(message);
    if (addToCurrentDay)
        currentDay->append(message);
}

//FIXME a lot of copy+paste
void Excel::generateHeaderLine(Excel::HeaderModeFlag flag)
{
    QString line;
    auto prefix = headersPrefix();

    if (!prefix.isEmpty())
        line.append(prefix);

    foreach (auto channel, channels)
    {
        //BUG? may be need to use testFlag?
        if (flag == Excel::HeaderModeFlag::LogName)
            line.append(channel->logName());

        if (flag == Excel::HeaderModeFlag::PlotName)
            line.append(channel->plotName());

        if (flag == Excel::HeaderModeFlag::WidgetName)
            line.append(channel->widgetName());

        if (!channel->postfix().isEmpty())
        {
            line.append(" (" + channel->postfix() + ")");
        }
        line.append(elementDelimeter);
    }
    appendToBuffers(line, currentDay->isCreated());
    appendToBuffers(lineDelimeter, currentDay->isCreated());
    line.clear();
}

void Excel::finishConfigureChild()
{
    if (headerMode.testFlag(Excel::LogName))
    {
        generateHeaderLine(Excel::LogName);
    }

    if (headerMode.testFlag(Excel::PlotName))
    {
        generateHeaderLine(Excel::PlotName);
    }

    if (headerMode.testFlag(Excel::WidgetName))
    {
        generateHeaderLine(Excel::WidgetName);
    }
}


void Excel::push()
{
    currentSession->push();
    currentDay->push();
}

QString Excel::formatDoubleValue(ChannelDouble *channel)
{

    return  EasyLiving::formatDouble(channel->value(),
                                     channel->precisionLog(),
                                     channel->scientificNotation(),
                                     false);

//    if (EasyLiving::isEqualDouble(value, 0))
//    {
//        return QString("0");
//    }

//    if ((0.001 < value) && (value < 2000))
//    {

//    }
//    else
//    {
//        return  EasyLiving::formatDouble(value, 3, true, EasyLiving::Comma, false);
//    }
}

void Excel::commit()
{
    QString line;
    QString value;

    auto prefix = commitPrefix();
    if (!prefix.isEmpty())
        line.append(prefix);

    foreach (auto channel, this->channels)
    {
        auto channel_double = dynamic_cast<ChannelDouble *>(channel);
        if (channel_double)
        {
            value = formatDoubleValue(channel_double);


            //value = QString("%1").arg(channel_double->value(), 0, 'e', 2, '0');
            line.append(value);
            line.append(elementDelimeter);
            continue;
        }

        auto channel_bool = dynamic_cast<ChannelBool *>(channel);
        if (channel_bool)
        {
            value = QString("%1").arg(channel_bool->value() ? 1 : 0);
            line.append(value);
            line.append(elementDelimeter);
            continue;
        }

        auto channel_qdatetime = dynamic_cast<ChannelT<QDateTime> *>(channel);
        if (channel_qdatetime)
        {
            value = channel_qdatetime->value().toString(EasyLiving::formatDateTimeFile());
            line.append(value);
            line.append(elementDelimeter);
            continue;
        }

        auto channelQStringTmp = dynamic_cast<ChannelQString *>(channel);
        if (channelQStringTmp)
        {
            if (channelQStringTmp->isLogged())
                continue;

            value = channelQStringTmp->value().simplified();
            channelQStringTmp->valueReadByLogger();
            line.append(value);
            line.append(elementDelimeter);
            continue;
        }
    }
    appendToBuffers(line);
    appendToBuffers(lineDelimeter);
}
