#ifndef BODYDETECTIONHTTPCLIENT_H
#define BODYDETECTIONHTTPCLIENT_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include "BodyTypes.h"
#include "network/HTTPClient.h"

class BodyDetectionHTTPClient : public HTTPClient
{
    Q_OBJECT

public:
    BodyDetectionHTTPClient();

    void initService(const QString& settingsFile);
    void sendPhoto(const QString& photoURL, BODY_REQUEST_TYPE type = BODY_REQUEST_TYPE::BODY_DETECT);

    void requestSuccessHandler(const QByteArray& data);

signals:
    void requestSuccessSignal(const QJsonObject&);
    void serviceErrorSignal();

protected slots:
    virtual void httpRequestSuccessHandler(QNetworkReply* reply);
    void requestFailedHandler();

private:
    QString BODY_URL      ;// = "https://api-us.faceplusplus.com/facepp/v3/detect";
    QString BODY_SEGMENT_URL;
    QString BODY_GESTURE_URL;
    QString API_KEY       ;// = "MA2zIsaERn-g6x3ngsfAjTGZLPylVh8b";
    QString API_SECRET    ;// = "s9Gn2v8GOe6w5WMCh8ywYMJIcVRUlxlh";
    int FACE_SERVER_TIMEOUT = 0;
    QString RETURN_ATTRIBUTES = "gender,cloth_color";
};

#endif // FACEDETECTIONREQUEST_H
