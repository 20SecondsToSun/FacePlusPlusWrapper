#include "FaceHolder.h"

FaceHolder::FaceHolder()
{

}

void FaceHolder::flush()
{
    _isReady = false;
}

bool FaceHolder::ready() const
{
    return _isReady;
}

void FaceHolder::newFaceData(const Face& face)
{
    _face = face;
    _isReady = true;
}

QVector<QPoint> FaceHolder::getFaceLandmark() const
{
    return _face.getLandmark();
}

QVector3D FaceHolder::getHeadPose() const
{
    return _face.getAttributes().headpose.getVector();
}

float FaceHolder::getBeauty()
{
    return _face.getAttributes().beauty.getFemaleScore();
}

double FaceHolder::getRoll() const
{
    return getHeadPose().y();
}

QPoint FaceHolder::getLeftEye() const
{
    return _face.getLeftEyeCenter();
}

QPoint FaceHolder::getRightEye() const
{
    return _face.getRightEyeCenter();
}

QRect FaceHolder::getFaceRect() const
{
    FaceRectangle rect = _face.getFaceRectangle();
    QRect _rect(rect.left, rect.top, rect.width, rect.height);
    return _rect;
}

QVector<int> FaceHolder::getFacePointsX() const
{
    return getPointsX(_face.getContourPoints());
}

QVector<int> FaceHolder::getFacePointsY() const
{
    return getPointsY(_face.getContourPoints());
}

QVector<int> FaceHolder::getConvexFacePointsX() const
{
    return getPointsX(_face.getConvexHull());
}

QVector<int> FaceHolder::getConvexFacePointsY() const
{
    return getPointsY(_face.getConvexHull());
}

QVector<int> FaceHolder::getPointsX(const QVector<QPoint>& points) const
{
    QVector<int> pointsX;
    for(int i = 0; i <points.size(); i++)
    {
        pointsX.push_back(points[i].x());
    }

    return pointsX;
}

QVector<int> FaceHolder::getPointsY(const QVector<QPoint>& points) const
{
    QVector<int> pointsY;
    for(int i = 0; i <points.size(); i++)
    {
        pointsY.push_back(points[i].y());
    }

    return pointsY;
}

