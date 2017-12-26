#ifndef FACEHOLDER_H
#define FACEHOLDER_H

#include <QPoint>
#include <QVector>
#include <QRect>
#include <QVector3D>
#include <QObject>
#include "FaceTypes.h"

class FaceHolder: public QObject
{
    Q_OBJECT

public:
    FaceHolder();

    Q_INVOKABLE QVector<QPoint> getFaceLandmark() const;
    Q_INVOKABLE QVector3D getHeadPose() const;

    Q_INVOKABLE float getBeauty();
    Q_INVOKABLE double getRoll() const;
    Q_INVOKABLE QRect getFaceRect() const;
    Q_INVOKABLE bool ready() const;
    Q_INVOKABLE void flush();

private:
    Face _face;
    bool _isReady = false;

public slots:
    void newFaceData(const Face& face);
};

#endif // FACEHOLDER_H
