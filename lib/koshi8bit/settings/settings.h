#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#include <lib/koshi8bit/easyliving.h>

class Settings
{
private:
    Settings();

public:
    static int iniReadInt(QSettings *settings, QString path, int defaultValue=0,
                          bool *okFind=nullptr, bool *okParce=nullptr);

    static double iniReadDouble(QSettings *settings, QString path, double defaultValue=0,
                          bool *okFind=nullptr, bool *okParce=nullptr);
};

#endif // SETTINGS_H
