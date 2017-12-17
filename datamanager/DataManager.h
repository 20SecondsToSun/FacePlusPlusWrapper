#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QFileDialog>

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);

     Q_INVOKABLE void open();

private:
    void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);
    bool loadFile(const QString &fileName);

signals:

public slots:
};

#endif // DATAMANAGER_H
