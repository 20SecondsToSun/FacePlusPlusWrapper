#ifndef FACEMERGEHTTPCLIENT_H
#define FACEMERGEHTTPCLIENT_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QFile>
#include "network/HTTPClient.h"

class FaceMergeHTTPClient : public HTTPClient
{
    Q_OBJECT

public:
    FaceMergeHTTPClient();

    void initService(const QString& settingsFile);
    void sendPhoto(const QString& photoURL1, const QString& photoURL2);

    void requestSuccessHandler(const QByteArray& data);

signals:
    void requestSuccessSignal(const QJsonObject&);
    void serviceErrorSignal();

protected slots:
    virtual void httpRequestSuccessHandler(QNetworkReply* reply);
    void requestFailedHandler();

private:
    QString FACE_MERGE_URL;
    QString API_KEY;
    QString API_SECRET;
    int FACE_SERVER_TIMEOUT = 0;
    QString RETURN_ATTRIBUTES = "headpose,gender,eyegaze,beauty";

    QFile* getPhotoFile(const QString& photoURL);
};


#endif // FACEMERGEHTTPCLIENT_H
