#include "easyliving.h"

QLocale EasyLiving::localeMy = QLocale(QLocale::Russian);

EasyLiving::EasyLiving()
{
    //THIS IS NOT STATIC CONSTRUCTOR
    //localeMy.setNumberOptions(QLocale::OmitGroupSeparator);
}



//double
QString EasyLiving::formatDouble(double value, int precision, bool scientificNotation, bool showGroupSeparator, EasyLiving::DoubleSeporatorSign seporatorSign)
{
    char _format= scientificNotation ? 'e' : 'f';

    switch (seporatorSign)
    {
        case DoubleSeporatorSign::Comma:
            if (showGroupSeparator)
            {
                return QLocale(QLocale::Russian).toString(value, _format, precision);
            }
            else
            {
                localeMy.setNumberOptions(QLocale::OmitGroupSeparator);
                return localeMy.toString(value, _format, precision);
            }

        case DoubleSeporatorSign::Point:
            return QString::number(value, _format, precision);
    }

    auto message = EL_FORMAT_ERR(tr("Invalid seporator sign!"));
    qDebug() << message;
    return message;
}

bool EasyLiving::isBetween(double value, double min, double max)
{
    return (value >= min) && (value <= max);
}

bool EasyLiving::isEqualDouble(double a, double b)
{
    return qAbs(a - b) <= std::numeric_limits<double>::epsilon();
}

bool EasyLiving::isBetween(QDateTime value, QDateTime min, QDateTime max)
{
    return (value >= min) && (value <= max);
}

int EasyLiving::sign(double x) {
    if (x > 0.0) return 1;
    if (x < 0.0) return -1;
    return 0;
}

QString EasyLiving::dateTimeDelta(QDateTime begin, QDateTime end, bool daysOnly, bool showMs)
{
    int years=0, months=0, days, hours, minutes, seconds, milliseconds;

    EasyLiving::dateTimeDelta(begin, end, years, months, days,
                              hours, minutes, seconds, milliseconds, daysOnly);
    QTime time(hours, minutes, seconds, milliseconds);

    QString message;

    messageAppend(message, years, "y");
    messageAppend(message, months, "m", (years!=0));
    messageAppend(message, days, "d", (years!=0)||(months!=0));
    message.append(time.toString(EasyLiving::formatTimeUi(showMs)));
    return message;
}


void EasyLiving::messageAppend(QString &message, int value, QString postfix, bool forseAppend)
{
    if ((value != 0) || forseAppend)
    {
        message.append(QString("%1%2 ")
                       .arg(value)
                       .arg(postfix));
    }
}

void EasyLiving::dateTimeDelta(QDateTime begin, QDateTime end, int &years, int &month, int &days,
                               int &hours, int &minutes, int &seconds, int &milliseconds, bool daysOnly)
{
    auto delta = qAbs(begin.toMSecsSinceEpoch() - end.toMSecsSinceEpoch());

    del(delta, milliseconds, 1000);
    del(delta, seconds, 60);
    del(delta, minutes, 60);
    del(delta, hours, 24);

    if (daysOnly)
    {
        days = static_cast<int>(delta);
    }
    else
    {
        del(delta, days, 30);
        del(delta, month, 12);
        years = static_cast<int>(delta);
    }
}

void EasyLiving::del(long long &delta, int &v, int divider)
{
    v = static_cast<int>(delta % divider);
    delta /= divider;
}



//dateTime
QString EasyLiving::formatDate()
{
    return "yyyy-MM-dd";
}

QString EasyLiving::formatDateFile()
{
    return formatDate();
}

QString EasyLiving::formatTimeFile(bool showMS)
{
    QString format = "hh-mm-ss";
    if (showMS)
        format += "--zzz";
    return format;
}

QString EasyLiving::formatDateTimeFileSeporator()
{
    return "--";
}

QString EasyLiving::formatDateTimeISO8601(bool showMS)
{
    QString format = "yyyy-MM-ddThh:mm:ss";
    if (showMS)
        format += ".zzz";
    return format;
}

QString EasyLiving::formatDateTimeFile(bool showMS)
{
    return formatDateFile() + formatDateTimeFileSeporator() + formatTimeFile(showMS);
}

QString EasyLiving::formatDateUi()
{
    return formatDate();
}

QString EasyLiving::formatTimeUi(bool showMS)
{
    QString format = "hh:mm:ss";
    if (showMS)
        format += ".zzz";
    return format;
}

QString EasyLiving::formatDateTimeUiSeporator(QString seporator)
{
    return seporator;
}

QString EasyLiving::formatDateTimeUi(bool showMS)
{
    return formatDateUi() + formatDateTimeUiSeporator() + formatTimeUi(showMS);
}

QString EasyLiving::postfixCelsius()
{
    return tr("°C");
}

QString EasyLiving::postfixAmpere()
{
    return tr("А");
}

QString EasyLiving::postfixAmpereEn()
{
    return "A";
}

QString EasyLiving::postfixVolt()
{
    return tr("В");
}

QString EasyLiving::postfixVoltEn()
{
    return tr("V");
}

QString EasyLiving::postfixEnergy()
{
    return tr("эВ");
}

QString EasyLiving::postfixEnergyEn()
{
    return "eV";
}

QString EasyLiving::postfixWatt()
{
    return tr("Вт");
}

QString EasyLiving::postfixSievert()
{
    return tr("Зв");
}

QString EasyLiving::postfixSievertEn()
{
    return "Sv";
}

QString EasyLiving::postfixSievertPerHour()
{
    return postfixSievert() + tr("/Ч");
}

QString EasyLiving::postfixSievertPerHourEn()
{
    return postfixSievertEn() + "/h";
}

QString EasyLiving::postfixPascal()
{
    return tr("Па");
}

QString EasyLiving::postfixFluence()
{
    return postfixMilliAmpere() + tr("ч");
}

QString EasyLiving::postfixFluenceEn()
{
    return postfixMilliAmpereEn() + tr("h");
}

QString EasyLiving::postfixPiece()
{
    return tr("шт");
}

QString EasyLiving::postfixVolume()
{
    return tr("л");
}

QString EasyLiving::postfixSecond()
{
    return tr("сек");
}

QString EasyLiving::postfixMinute()
{
    return tr("мин");
}

QString EasyLiving::postfixHour()
{
    return tr("час");
}

QString EasyLiving::postfixPiecePerSecond()
{
    return postfixPiece() +tr("/") + postfixSecond();
}

QString EasyLiving::postfixVolumePerMinute()
{
    return postfixVolume() +tr("/") + postfixMinute();
}

QString EasyLiving::postfixMilli()
{
    return tr("м");
}

QString EasyLiving::postfixMilliEn()
{
    return "m";
}

QString EasyLiving::postfixKilo()
{
    return tr("к");
}

QString EasyLiving::postfixKiloEn()
{
    return "k";
}

QString EasyLiving::postfixMega()
{
    return tr("М");
}

QString EasyLiving::postfixMegaEn()
{
    return "M";
}

QString EasyLiving::postfixPersent()
{
    return tr("%");
}

QString EasyLiving::postfixMilliAmpere()
{
    return postfixMilli() + postfixAmpere();
}

QString EasyLiving::postfixMilliAmpereEn()
{
    return postfixMilliEn() + postfixAmpere();
}

QString EasyLiving::postfixKiloVolt()
{
    return EasyLiving::postfixKilo() + EasyLiving::postfixVolt();
}

QString EasyLiving::postfixKiloVoltEn()
{
    return postfixKiloEn() + postfixVoltEn();
}

bool EasyLiving::isChecked(int arg1)
{
    return arg1 == 2 ? true : false;
}

bool EasyLiving::fileExists(QString path)
{
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isFile();
}

bool EasyLiving::dirExists(QString path)
{
    //return QDir(path).exists();
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isDir();
}

bool EasyLiving::createDir(QString path)
{
    QDir dir(path);
    return dir.mkpath(".");
}

bool EasyLiving::isWritable(QString path)
{
    auto file = QDateTime::currentDateTime().toString(formatDateTimeFile()) + ".txt";
    auto tmpFile = pathConcat(path, file);

    auto result = true;
    auto testStr = "I love my dog Cooper!";
    result &= writeFile(tmpFile, testStr);
    result &= readFile(tmpFile) == testStr;

    QFile file1(tmpFile);

    if (file1.exists())
        file1.remove();

    return result;
}

bool EasyLiving::writeFile(QString path, QString text, bool append, bool addDateTime, QString codepage)
{
    QFile file(path);


    if (addDateTime)
    {
        auto time = QDateTime::currentDateTime().toString(EasyLiving::formatDateTimeUi(true));
        text = QString("%1: %2\n")
                .arg(time)
                .arg(text);
    }

    QIODevice::OpenMode flags = QIODevice::WriteOnly;
    if (append) {
        flags |= QIODevice::Append;
    }

    if (file.open(flags)) {
        QTextStream stream(&file);
        if (!codepage.isEmpty()) {
#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 2))
                stream->setEncoding(codepage.toStdString().c_str());
#endif

        }

        stream << text;
        return true;
    }
    else
    {
        return false;
    }
}

QString EasyLiving::readFile(QString path, bool *ok)
{
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << EL_FORMAT_ERR("error opening file:") << file.error();
        if (ok != nullptr)
            *ok = false;
        return "";
    }

    QTextStream instream(&file);
    QString line = instream.readAll();

    file.close();

    if (ok != nullptr)
        *ok = true;

    return line;

}

QString EasyLiving::pathConcat(QString path1, QString path2)
{
    path1 = QDir::fromNativeSeparators(path1);
    path2 = QDir::fromNativeSeparators(path2);
    auto finalPath = QDir(path1).filePath(path2);
    return finalPath;
}

bool EasyLiving::exec(QString exe, QStringList arguments)
{
    QProcess process;
    process.setProgram(exe);
    process.setArguments(arguments);
    return process.startDetached();
}

bool EasyLiving::exec(QString cmdLine)
{
    return QProcess::startDetached(cmdLine);
}

OperationResult EasyLiving::readJson(QString path)
{
    if (!EasyLiving::fileExists(path)) {
        auto msg = tr("Файл '%1' не найден").arg(path);
        qCritical() << EL_FORMAT_ERR(msg);
        return OperationResult(false, msg);
    }

    QFile jsonFile(path);
    jsonFile.open(QFile::ReadOnly);
    QJsonParseError jsonError;
    auto conf = QJsonDocument().fromJson(jsonFile.readAll(), &jsonError);
    jsonFile.close();

    if( jsonError.error != QJsonParseError::NoError )
    {
        auto msg = tr("QJsonParseError: %1").arg(jsonError.errorString());
        qCritical() << EL_FORMAT_ERR(msg);
        return OperationResult(false, msg);
    }

    if (conf.isObject()) {
        auto conf2 = new QJsonDocument(conf);
        return OperationResult(true, "", (void *)conf2);
    } else {
        auto msg = tr("!conf.isObject()");
        qCritical() << EL_FORMAT_ERR(msg);
        return OperationResult(false, msg);
    }

}

OperationResult EasyLiving::writeJson(QString path, QJsonDocument doc)
{
    QFile jsonFile(path);

    if (!jsonFile.open(QFile::WriteOnly)) {
        auto msg = tr("Не удалось открыть файл");
        qCritical() << EL_FORMAT_ERR(msg);
        return OperationResult(false, msg);
    }

    if (jsonFile.write(doc.toJson()) == -1) {
        auto msg = tr("Не удалось сохранить в файл");
        qCritical() << EL_FORMAT_ERR(msg);
        return OperationResult(false, msg);
    }

    return OperationResult(true);
}



QString EasyLiving::setWindowTitle(QString text, QString version)
{
    return QString("%1 v%2 /// Aleksey K. [koshi8bit]")
        .arg(text)
        .arg(version);
}

