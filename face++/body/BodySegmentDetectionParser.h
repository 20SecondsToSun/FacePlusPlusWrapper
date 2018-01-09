#ifndef BODYSEGMENTDETECTIONPARSER_H
#define BODYSEGMENTDETECTIONPARSER_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include <QImage>
#include "face++/body/bodytypes.h"

class BodySegmentDetectionParser : public QObject
{
    Q_OBJECT
public:
    explicit BodySegmentDetectionParser(QObject *parent = nullptr);
    bool saveBodyGrayScale(const QString& filename);
    void parse(const QJsonObject& jsonObject);

private:
    QString image_id;
    QString request_id;
    QString grayScaleBase64;
};

#endif // BODYSEGMENTDETECTIONPARSER_H
