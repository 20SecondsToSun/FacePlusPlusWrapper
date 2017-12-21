#ifndef FACEPLUSPLUSCONFIG_H
#define FACEPLUSPLUSCONFIG_H

#include <QApplication>
#include <QSettings>

class FacePlusPlusConfig
{
public:
    explicit FacePlusPlusConfig();
    void load();
    QString getSettingsFile() const;

private:
    QString settingsFile = qApp->applicationDirPath() + "/content/settings.ini";

};

#endif // FACEPLUSPLUSCONFIG_H
