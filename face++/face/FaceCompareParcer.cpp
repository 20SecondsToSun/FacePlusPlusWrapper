#include "FaceCompareParcer.h"

FaceCompareParcer::FaceCompareParcer()
{

}

void FaceCompareParcer::parse(const QJsonObject& jsonObject)
{
   auto confidence = jsonObject["confidence"].toDouble();
   qDebug()<<"FaceCompareParcer "<<confidence;
}

