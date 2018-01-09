#include "BodyGestureDetectionParser.h"

BodyGestureDetectionParser::BodyGestureDetectionParser(QObject *parent) : QObject(parent)
{

}

void BodyGestureDetectionParser::parse(const QJsonObject& jsonObject)
{
    QJsonArray handsJson = jsonObject["hands"].toArray();

    if(handsJson.size() != 0)
    {
        for(int i = 0; i < handsJson.size(); i++)
        {
            Hand hand;
            QJsonObject handJson = handsJson[i].toObject();
            auto x = handJson["hand_rectangle"].toObject()["left"].toInt();
            auto y = handJson["hand_rectangle"].toObject()["top"].toInt();
            auto width = handJson["hand_rectangle"].toObject()["width"].toInt();
            auto height = handJson["hand_rectangle"].toObject()["height"].toInt();
            hand.setHandRectangle(QRect(x, y, width, height));

            Gesture gesture;
            gesture.parse(handJson["gesture"].toObject());

            hand.setGesture(gesture);

            hands.push_back(hand);
        }
    }
}

bool BodyGestureDetectionParser::noHands() const
{
    return hands.empty();;
}

QVector<Hand> BodyGestureDetectionParser::getHands() const
{
     return hands;
}
