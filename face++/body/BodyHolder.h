#ifndef BODYHOLDER_H
#define BODYHOLDER_H

#include <QObject>
#include "face++/body/BodyTypes.h"


class BodyHolder : public QObject
{
    Q_OBJECT
public:
    explicit BodyHolder(QObject *parent = nullptr);

    Q_INVOKABLE bool ready() const;
    Q_INVOKABLE void flush();
    Q_INVOKABLE QRect getBodyRect() const;

signals:

public slots:
    void newBodyData(const Body& body);

private:
    bool _isReady = false;
    Body _body;
};

#endif // BODYHOLDER_H
