#ifndef FACETYPES_H
#define FACETYPES_H

#include <QRect>
#include <QVector2D>
#include <QVector3D>
#include <QObject>
#include <QVector>
#include <QPoint>
#include <QSharedPointer>

enum class FACE_API_METHOD
{
    DETECT,
    COMPARE
};

struct FaceRectangle
{
    FaceRectangle(float t, float l, float w, float h):
        top(t), left(l), width(w), height(h)
    {

    }

    FaceRectangle()
    {

    }

    float top;
    float left;
    float width;
    float height;
};

class Beauty
{
    float femaleScore = 0;
    float maleScore = 0;

public:
    float getFemaleScore() const
    {
        return femaleScore;
    }

    float getMaleScore() const
    {
        return maleScore;
    }

    void setFemaleScore(float value)
    {
        femaleScore = value;
    }

    void setMaleScore(float value)
    {
        maleScore = value;
    }
};

struct Eye
{
    float positionXCoordinate;
    float positionYCoordinate;
    QVector3D vector;
};

struct Eyegaze
{
    Eye leftEye;
    Eye rightEye;
};

struct HeadPose
{
    float pitch;
    float roll;
    float yaw;

    QVector3D getVector()
    {
        return QVector3D(pitch, roll, yaw);
    }
};

struct FaceAttributes
{
    QString gender;
    HeadPose headpose;
    Beauty beauty;
    Eyegaze eyegaze;
    QPoint leftEyePosition;
    QPoint rightEyePosition;

    void setBeauty(float maleScore, float femaleScore)
    {
        beauty.setMaleScore(maleScore);
        beauty.setFemaleScore(femaleScore);
    }
};

class Face
{
    QString token;
    QVector<QPoint> landmark;
    FaceAttributes attributes;
    FaceRectangle faceRectangle;

public:
    Face(){}

    void setToken(const QString& token)
    {
        this->token = token;
    }

    QString getToken() const
    {
        return token;
    }

    void setFaceRectangle(const FaceRectangle& faceRectangle)
    {
        this->faceRectangle = faceRectangle;
    }

    FaceRectangle getFaceRectangle() const
    {
        return faceRectangle;
    }

    void setLandmark(const QVector<QPoint>& landmark)
    {
        this->landmark = landmark;
    }    

    QVector<QPoint> getLandmark() const
    {
        return landmark;
    }

    void setAttributes(const FaceAttributes& attributes)
    {
        this->attributes = attributes;
    }

    FaceAttributes getAttributes() const
    {
        return attributes;
    }

    Beauty getBeauty() const
    {
        return attributes.beauty;
    }

};
#endif // FACETYPES_H
