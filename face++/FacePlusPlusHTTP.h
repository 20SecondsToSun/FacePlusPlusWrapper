#ifndef FACEPLUSPLUSHTTP_H
#define FACEPLUSPLUSHTTP_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QFile>
#include <QHttpMultiPart>
#include "network/HTTPClient.h"

class FacePlusPlusHTTP: public HTTPClient
{
    Q_OBJECT

public:
    FacePlusPlusHTTP();

signals:
    void requestSuccessSignal(const QJsonObject&);
    void serviceErrorSignal();

protected slots:
    virtual void httpRequestSuccessHandler(QNetworkReply* reply);
    virtual void requestFailedHandler();

protected:
    int FACE_SERVER_TIMEOUT = 0;
    QString API_KEY;
    QString API_SECRET;

    QFile* getPhotoFile(const QString& photoURL);
    virtual void addLoginPart(QHttpMultiPart* multiPart);
};

#endif // FACEPLUSPLUSHTTP_H
