#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <QApplication>
#include <QSettings>

class Config : public QObject
{
     Q_OBJECT
public:
    Config();
    void load();
    QString getSettingsFile() const;


private:
    QString settingsFile = qApp->applicationDirPath() + "/content/settings.ini";
};

#endif // CONFIG_H
