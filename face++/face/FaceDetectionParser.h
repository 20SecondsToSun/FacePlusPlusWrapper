#ifndef FACEDETECTIONPARCER_H
#define FACEDETECTIONPARCER_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include "FaceTypes.h"

class FaceDetectionParcer
{
    QVector<Face> faces;

public:
    FaceDetectionParcer();

    void parse(const QJsonObject& faces);
    QVector<Face> getFaces() const;
    bool noFaces() const;

};

#endif // FACEDETECTIONPARCER_H
