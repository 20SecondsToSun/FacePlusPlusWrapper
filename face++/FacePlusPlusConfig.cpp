#include "FacePlusPlusConfig.h"

FacePlusPlusConfig::FacePlusPlusConfig()
{

}

void FacePlusPlusConfig::load()
{
   QSettings settings(settingsFile, QSettings::IniFormat);
}

QString FacePlusPlusConfig::getSettingsFile() const
{
    return settingsFile;
}

