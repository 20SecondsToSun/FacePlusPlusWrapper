#ifndef FACECOMPAREPARCER_H
#define FACECOMPAREPARCER_H

#include <QJsonObject>
#include <QDebug>
#include "FaceTypes.h"

class FaceCompareParcer
{
public:
    explicit FaceCompareParcer();
    void parse(const QJsonObject& faces);
};

#endif // FACECOMPAREPARCER_H
