#ifndef BODYDETECTIONHTTPCLIENT_H
#define BODYDETECTIONHTTPCLIENT_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include "BodyTypes.h"
#include "network/HTTPClient.h"
#include "../FacePlusPlusHTTP.h"

class BodyDetectionHTTPClient : public FacePlusPlusHTTP
{
    Q_OBJECT

public:
    BodyDetectionHTTPClient();

    void initService(const QString& settingsFile);
    void sendPhoto(const QString& photoURL, BODY_REQUEST_TYPE type = BODY_REQUEST_TYPE::BODY_DETECT);

private:
    QString BODY_URL;
    QString BODY_SEGMENT_URL;
    QString BODY_GESTURE_URL;
    QString RETURN_ATTRIBUTES = "gender,cloth_color";
};

#endif // FACEDETECTIONREQUEST_H
