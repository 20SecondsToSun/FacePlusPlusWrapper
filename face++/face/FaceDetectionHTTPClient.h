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
    void faceDetect(const QString& photoURL);
    void faceCompare(const QString& photoURL1, const QString& photoURL2);

private:
    QString FACE_URL;
    QString FACE_COMPARE_URL;
    QString RETURN_ATTRIBUTES = "headpose,gender,eyegaze,beauty";
};

#endif // FACEDETECTIONREQUEST_H
