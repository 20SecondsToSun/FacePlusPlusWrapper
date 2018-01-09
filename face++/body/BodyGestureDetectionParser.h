#ifndef BODYGESTUREDETECTIONPARSER_H
#define BODYGESTUREDETECTIONPARSER_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include <QVector>
#include <QJsonArray>
#include "face++/body/BodyTypes.h"

class BodyGestureDetectionParser : public QObject
{
    Q_OBJECT
public:
    explicit BodyGestureDetectionParser(QObject *parent = nullptr);

    void parse(const QJsonObject& hands);
    bool noHands() const;
    QVector<Hand> getHands() const;

private:
    QVector<Hand> hands;
};

#endif // BODYGESTUREDETECTIONPARSER_H
