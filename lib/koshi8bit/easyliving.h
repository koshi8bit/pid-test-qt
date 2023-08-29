#ifndef EASYLIVING_H
#define EASYLIVING_H

//https://github.com/koshi8bit/lib

#include <QObject>
#include <QString>
#include <QLocale>
#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <QProcess>
#include <QTimer>
#include <QJsonDocument>

#include "operationresult.h"


//errors
#define EL_FORMAT_ERR(message) (QStringList() << "ACHTUNG! " << Q_FUNC_INFO << ": " << message).join("")

//variables
// QT_MESSAGE_PATTERN "%{time HH:mm:ss.zzz} >>> %{function} %{message}"
#define EL_F Q_FUNC_INFO
#define EL_NAME(Variable) (#Variable)

// #define EL_GET_VARIABLE_NAME(Variable) (#Variable) //TODO delete later


//raw string
//R"(raw\string)"
class EasyLiving : public QObject
{
    Q_OBJECT

public:
    enum DoubleSeporatorSign
    {
        Comma,
        Point
    };
    Q_ENUM(DoubleSeporatorSign)

    EasyLiving();

    //double
    static QLocale localeMy;
    //fixme double value, int precision = 3, bool scientificNotation = false, bool showGroupSeparator = false, bool seporatorPoint = false)
    static QString formatDouble(double value, int precision = 3, bool scientificNotation = false, bool showGroupSeparator = true, DoubleSeporatorSign seporatorSign = DoubleSeporatorSign::Comma);
//    QT_DEPRECATED_X(
//        "Testing QT_DEPRECATED_X"
//        )
    static bool isBetween(double value, double min, double max);
    static bool isEqualDouble(double a, double b);

    static int sign(double x);


    //dateTime
    static bool isBetween(QDateTime value, QDateTime min, QDateTime max);
    static QString dateTimeDelta(QDateTime begin, QDateTime end, bool daysOnly = true, bool showMs = false);
    static void dateTimeDelta(QDateTime begin, QDateTime end, int &years, int &month, int &days,
                              int &hours, int &minutes, int &seconds, int &milliseconds, bool daysOnly = true);


    static QString formatDateTimeISO8601(bool showMS);
    static QString formatDate();

    static QString formatDateFile();
    static QString formatTimeFile(bool showMS);
    static QString formatDateTimeFileSeporator();
    static QString formatDateTimeFile(bool showMS = false);

    static QString formatDateUi();
    static QString formatTimeUi(bool showMS = false);
    static QString formatDateTimeUiSeporator(QString seporator = "@");
    static QString formatDateTimeUi(bool showMS = false);


    //postfix
    static QString postfixCelsius();
    static QString postfixAmpere();
    static QString postfixAmpereEn();
    static QString postfixVolt();
    static QString postfixVoltEn();
    static QString postfixEnergy();
    static QString postfixEnergyEn();
    static QString postfixWatt();
    static QString postfixSievert();
    static QString postfixSievertEn();
    static QString postfixSievertPerHour();
    static QString postfixSievertPerHourEn();
    static QString postfixPascal();
    static QString postfixFluence();
    static QString postfixFluenceEn();
    static QString postfixPiece();
    static QString postfixVolume();

    static QString postfixSecond();
    static QString postfixMinute();
    static QString postfixHour();

    static QString postfixPiecePerSecond();
    static QString postfixVolumePerMinute();

    static QString postfixMilli();
    static QString postfixMilliEn();
    static QString postfixKilo();
    static QString postfixKiloEn();
    static QString postfixMega();
    static QString postfixMegaEn();

    static QString postfixPersent();

    static QString postfixMilliAmpere();
    static QString postfixMilliAmpereEn();
    static QString postfixKiloVolt();
    static QString postfixKiloVoltEn();


    //bool
    static bool isChecked(int arg1);

    //files
    static bool fileExists(QString path);
    static bool dirExists(QString path);
    static bool createDir(QString path);
    static bool isWritable(QString path);
    static bool writeFile(QString path, QString text, bool append = false, bool addDateTime = false, QString codec = "");
    static QString readFile(QString path, bool *ok=nullptr);
    static QString pathConcat(QString path1, QString path2);

    static bool exec(QString exe, QStringList arguments);
    static bool exec(QString cmdLine);

    //JSON
    static OperationResult readJson(QString path);
    static OperationResult writeJson(QString path, QJsonDocument doc);

    //ui
    static QString setWindowTitle(QString text, QString version);

private:
    static void del(long long &delta, int &v, int divider);
    static void messageAppend(QString &message, int value, QString postfix, bool forseAppend = false);




};

#endif // EASYLIVING_H
