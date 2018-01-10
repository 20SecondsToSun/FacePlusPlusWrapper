#ifndef FACEDETECTIONREQUEST_H
#define FACEDETECTIONREQUEST_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include "FaceTypes.h"
#include "network/HTTPClient.h"
#include "../FacePlusPlusHTTP.h"

class FaceDetectionHTTPClient : public FacePlusPlusHTTP
{
    Q_OBJECT

public:
    FaceDetectionHTTPClient();
    void initService(const QString& settingsFile);
    void sendPhoto(const QString& photoURL);

private:
    QString FACE_URL;
    QString RETURN_ATTRIBUTES = "headpose,gender,eyegaze,beauty";
};

#endif // FACEDETECTIONREQUEST_H
