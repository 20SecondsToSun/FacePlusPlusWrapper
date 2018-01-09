#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    virtual void run(const QString&){};
    virtual void run(const QString& path1, const QString& path2){};

    virtual void init() = 0;
    virtual ~Controller(){};

signals:

public slots:
};

#endif // CONTROLLER_H
