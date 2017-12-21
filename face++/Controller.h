#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    virtual void run(const QString&) = 0;
    virtual void init() = 0;
    virtual ~Controller(){};

signals:

public slots:
};

#endif // CONTROLLER_H
