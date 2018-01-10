#ifndef FACEMERGEHTTPCLIENT_H
#define FACEMERGEHTTPCLIENT_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QFile>
#include "network/HTTPClient.h"
#include "../FacePlusPlusHTTP.h"

class FaceMergeHTTPClient : public FacePlusPlusHTTP
{
    Q_OBJECT

public:
    FaceMergeHTTPClient();
    void initService(const QString& settingsFile);
    void sendPhoto(const QString& photoURL1, const QString& photoURL2);

private:
    QString FACE_MERGE_URL;   
    QString RETURN_ATTRIBUTES = "headpose,gender,eyegaze,beauty";    
};

#endif // FACEMERGEHTTPCLIENT_H
