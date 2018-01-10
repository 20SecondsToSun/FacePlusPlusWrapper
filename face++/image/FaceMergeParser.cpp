#include "FaceMergeParser.h"

FaceMergeParser::FaceMergeParser(QObject *parent) : QObject(parent)
{

}

void FaceMergeParser::parse(const QJsonObject& jsonObject)
{
    qDebug()<<"FaceMergeParser:  ";
    qDebug()<<jsonObject;

}
