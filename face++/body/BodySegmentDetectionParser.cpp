#include "BodySegmentDetectionParser.h"

BodySegmentDetectionParser::BodySegmentDetectionParser(QObject *parent) : QObject(parent)
{

}

void BodySegmentDetectionParser::parse(const QJsonObject& jsonObject)
{
    image_id = jsonObject["image_id"].toString();
    request_id = jsonObject["request_id"].toString();
    grayScaleBase64 = jsonObject["result"].toString();

    qDebug()<<"BodySegmentDetectionParser image_id"<<image_id;
}

bool BodySegmentDetectionParser::saveBodyGrayScale(const QString& filename)
{
   QImage image;
   image.loadFromData(QByteArray::fromBase64(grayScaleBase64.toUtf8()), "jpg");
   return image.save(filename);
}


