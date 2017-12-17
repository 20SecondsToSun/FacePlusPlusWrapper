#include "BodyDetectionParser.h"
#include <QJsonArray>

BodyDetectionParser::BodyDetectionParser()
{

}

void BodyDetectionParser::parse(const QJsonObject& jsonObject)
{
    QJsonArray bodiesJson = jsonObject["humanbodies"].toArray();

    qDebug() << "bodiesJson::::::: " << bodiesJson;

    if(bodiesJson.size() != 0)
    {
        for(int i = 0; i < bodiesJson.size(); i++)
        {
            Body body;
            QJsonObject bodyJson = bodiesJson[i].toObject();
            body.setConfidence(bodyJson["confidence"].toString());

            auto x = bodyJson["humanbody_rectangle"].toObject()["left"].toInt();
            auto y = bodyJson["humanbody_rectangle"].toObject()["top"].toInt();
            auto width = bodyJson["humanbody_rectangle"].toObject()["width"].toInt();
            auto height = bodyJson["humanbody_rectangle"].toObject()["height"].toInt();

            body.setHumanbodyRectangle(QRect(x, y, width, height));

            bodies.push_back(body);
        }
    }
}

bool BodyDetectionParser::noBodies() const
{
    return bodies.empty();;
}

QVector<Body> BodyDetectionParser::getBodies() const
{
     return bodies;
}
