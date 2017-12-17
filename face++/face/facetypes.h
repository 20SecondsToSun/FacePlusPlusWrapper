#ifndef FACETYPES_H
#define FACETYPES_H

#include <QRect>
#include <QVector2D>
#include <QVector3D>
#include <QObject>
#include <QVector>
#include <QPoint>
#include <QSharedPointer>

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
    QVector<QPoint> convexHull;
    QVector<QPoint> contourPoints;
    FaceAttributes attributes;
    FaceRectangle faceRectangle;
    QPoint firstPoint, lastPoint;

public:
    Face(){}

    void setFirstPoint(const QPoint& value)
    {
        firstPoint = value;
    }

    void setLastPoint(const QPoint& value)
    {
        lastPoint =  value;
    }

    QPoint getFirstPoint() const
    {
        return firstPoint;
    }

    QPoint getLastPoint() const
    {
        return lastPoint;
    }

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

    void setConvexHull(const QVector<QPoint>& convexHull)
    {
        this->convexHull = convexHull;
    }

    QVector<QPoint> getConvexHull() const
    {
        return convexHull;
    }

    void setContourPoints(const QVector<QPoint>& points)
    {
        this->contourPoints = points;
    }

    QVector<QPoint> getContourPoints() const
    {
        return contourPoints;
    }  

    int getLeftX()
    {
        if(contourPoints.empty())
        {
            return 0;
        }

        int minX = contourPoints[0].x();

        for(int i = 0 ; i < contourPoints.size(); ++i)
        {
            if (contourPoints[i].x() < minX)
            {
                minX = contourPoints[i].x();
            }
        }

        return minX;
    }

    int getTopY()
    {
        if(contourPoints.empty())
        {
            return 0;
        }

        int topY = contourPoints[0].y();

        for(int i = 0 ; i < contourPoints.size(); ++i)
        {
            if (contourPoints[i].y() < topY)
            {
                topY = contourPoints[i].y();
            }
        }

        return topY;
    }

    int getRightX()
    {
        if(contourPoints.empty())
        {
            return 0;
        }

        int maxX = contourPoints[0].x();

        for(int i = 0 ; i < contourPoints.size(); ++i)
        {
            if (contourPoints[i].x() > maxX)
            {
                maxX = contourPoints[i].x();
            }
        }

        return maxX;
    }

    int getBottomY()
    {
        if(contourPoints.empty())
        {
            return 0;
        }

        int bottomY = contourPoints[0].y();

        for(int i = 0 ; i < contourPoints.size(); ++i)
        {
            if (contourPoints[i].y() > bottomY)
            {
                bottomY = contourPoints[i].y();
            }
        }

        return bottomY;
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

    QPoint getRightEyeCenter() const
    {
        return attributes.leftEyePosition;
    }

    QPoint  getLeftEyeCenter() const
    {
        return attributes.rightEyePosition;
    }

};
#endif // FACETYPES_H
