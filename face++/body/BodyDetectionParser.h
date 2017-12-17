#ifndef BODYDETECTIONPARSER_H
#define BODYDETECTIONPARSER_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include "face++/bodytypes.h"

class BodyDetectionParser
{
    QVector<Body> bodies;

public:
    explicit BodyDetectionParser();

   void parse(const QJsonObject& bodies);
   bool noBodies() const;
   QVector<Body> getBodies() const;

};

#endif // BODYDETECTIONPARSER_H
