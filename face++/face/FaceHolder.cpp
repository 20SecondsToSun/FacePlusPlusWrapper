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

QRect FaceHolder::getFaceRect() const
{
    FaceRectangle rect = _face.getFaceRectangle();
    QRect _rect(rect.left, rect.top, rect.width, rect.height);
    return _rect;
}
