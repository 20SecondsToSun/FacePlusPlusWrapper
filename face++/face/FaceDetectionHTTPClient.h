#ifndef FACEDETECTIONREQUEST_H
#define FACEDETECTIONREQUEST_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include "FaceTypes.h"
#include "network/HTTPClient.h"

class FaceDetectionHTTPClient : public HTTPClient
{
    Q_OBJECT

public:
    FaceDetectionHTTPClient();

    void initService(const QString& settingsFile);
    void sendPhoto(const QString& photoURL);

    void requestSuccessHandler(const QByteArray& data);

signals:
    void faceNotFoundSignal();
    void faceRecognizedSignal(const QVector<Face>& faces);
    void serviceErrorSignal();

protected slots:
    virtual void httpRequestSuccessHandler(QNetworkReply* reply);
    void requestFailedHandler();

private:
    QString FACE_URL      ;// = "https://api-us.faceplusplus.com/facepp/v3/detect";
    QString API_KEY       ;// = "MA2zIsaERn-g6x3ngsfAjTGZLPylVh8b";
    QString API_SECRET    ;// = "s9Gn2v8GOe6w5WMCh8ywYMJIcVRUlxlh";
    int FACE_SERVER_TIMEOUT = 0;
};

#endif // FACEDETECTIONREQUEST_H
