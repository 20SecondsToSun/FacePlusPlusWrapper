#include "config.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>

Config::Config()
{

}

void Config::load()
{
   QSettings settings(settingsFile, QSettings::IniFormat);
}

QString Config::getSettingsFile() const
{
    return settingsFile;
}
