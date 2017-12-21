#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QFileDialog>

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DATAMANAGER_H
