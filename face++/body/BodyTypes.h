#ifndef BODYTYPES_H
#define BODYTYPES_H

#include <QString>
#include <QRect>
#include <QDebug>
#include <QJsonObject>

enum class BODY_REQUEST_TYPE
{
    BODY_DETECT,
    SEGMENT,
    GESTURE
};

class Body
{
    QRect humanbodyRectangle;
    int confidence;

public:
    Body()
    {

    }

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

enum class GESTURE_TYPE
{
    BEG,
    BIG_V,
    DOUBLE_FINGER_UP,
    FIST,
    HAND_OPEN,
    HEART_A,
    HEART_B,
    HEART_C,
    HEART_D,
    INDEX_FINGER_UP,
    NAMASTE,
    PALM_UP,
    PHONECALL,
    ROCK,
    THANKS,
    THUMB_DOWN,
    THUMB_UP,
    UNKNOWN,
    VICTORY
};

class Gesture
{
    GESTURE_TYPE type;

public:
    void parse(const QJsonObject& jsonObject)
    {
        auto beg = jsonObject["beg"].toDouble();
        auto big_v = jsonObject["big_v"].toDouble();
        auto double_finger_up = jsonObject["double_finger_up"].toDouble();
        auto fist = jsonObject["fist"].toDouble();
        auto hand_open = jsonObject["hand_open"].toDouble();
        auto heart_a = jsonObject["heart_a"].toDouble();
        auto heart_b = jsonObject["heart_b"].toDouble();
        auto heart_c = jsonObject["heart_c"].toDouble();
        auto heart_d = jsonObject["heart_d"].toDouble();
        auto index_finger_up = jsonObject["index_finger_up"].toDouble();
        auto namaste = jsonObject["namaste"].toDouble();
        auto palm_up = jsonObject["palm_up"].toDouble();
        auto phonecall = jsonObject["phonecall"].toDouble();
        auto rock = jsonObject["rock"].toDouble();
        auto thanks = jsonObject["thanks"].toDouble();
        auto thumb_down = jsonObject["thumb_down"].toDouble();
        auto thumb_up = jsonObject["thumb_up"].toDouble();
        auto unknown = jsonObject["unknown"].toDouble();
        auto victory = jsonObject["victory"].toDouble();
    }
};

class Hand
{
    // QString image_id;
    //   QString request_id;
    //  int time_used;

    Gesture gesture;
    QRect handRectangle;

public:
    Hand(){}

    //    void setImageId(const QString& image_id)
    //    {
    //        this->image_id = image_id;
    //    }

    //    void setRequestId(const QString& request_id)
    //    {
    //        this->request_id = request_id;
    //    }

    //    void setTimeUsed(int time_used)
    //    {
    //        this->time_used = time_used;
    //    }

    void setGesture(const Gesture& gesture)
    {
        this->gesture = gesture;
    }

    void setHandRectangle(const QRect& handRectangle)
    {
        this->handRectangle = handRectangle;
    }
};

#endif // BODYTYPES_H
