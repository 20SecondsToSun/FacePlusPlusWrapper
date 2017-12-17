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
    Q_INVOKABLE QPoint getLeftEye() const;
    Q_INVOKABLE QPoint getRightEye() const;
    Q_INVOKABLE QRect getFaceRect() const;

    Q_INVOKABLE QVector<int> getFacePointsX() const;
    Q_INVOKABLE QVector<int> getFacePointsY() const;

    Q_INVOKABLE QVector<int> getConvexFacePointsX() const;
    Q_INVOKABLE QVector<int> getConvexFacePointsY() const;
    Q_INVOKABLE bool ready() const;
    Q_INVOKABLE void flush();

private:
    Face _face;
    QVector<int> getPointsX(const QVector<QPoint>& points) const;
    QVector<int> getPointsY(const QVector<QPoint>& points) const;
    bool _isReady = false;

public slots:
    void newFaceData(const Face& face);
};

#endif // FACEHOLDER_H
