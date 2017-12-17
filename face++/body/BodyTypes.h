#ifndef BODYTYPES_H
#define BODYTYPES_H

#include <QString>
#include <QRect>

class Body
{
    QRect humanbodyRectangle;
    int confidence;

public:
    Body(){}

    void setConfidence(const QString& confidence)
    {
        this->confidence = confidence.toInt();
    }

    void setHumanbodyRectangle(const QRect& humanbodyRectangle)
    {
        this->humanbodyRectangle = humanbodyRectangle;
    }

    QRect getHumanbodyRectangle() const
    {
       return humanbodyRectangle;
    }

};

#endif // BODYTYPES_H
