#include "settings.h"

Settings::Settings()
{

}

int Settings::iniReadInt(QSettings *settings, QString path, int defaultValue, bool *okFind, bool *okParce)
{
    if (!settings->contains(path))
    {
        qCritical() << EL_FORMAT_ERR("Path " + path + " not found in INI file");

        if (okFind)
            *okFind = false;

        return defaultValue;
    }

    if (okFind)
        *okFind = true;


    return settings->value(path, defaultValue).toInt(okParce);
}

double Settings::iniReadDouble(QSettings *settings, QString path, double defaultValue, bool *okFind, bool *okParce)
{
    if (!settings->contains(path))
    {
        qCritical() << EL_FORMAT_ERR("Path " + path + " not found in INI file");

        if (okFind)
            *okFind = false;

        return defaultValue;
    }

    if (okFind)
        *okFind = true;


    return settings->value(path, defaultValue).toDouble(okParce);
}
