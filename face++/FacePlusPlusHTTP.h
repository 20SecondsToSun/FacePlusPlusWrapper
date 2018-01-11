#ifndef FACEPLUSPLUSHTTP_H
#define FACEPLUSPLUSHTTP_H

#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QFile>
#include <QHttpMultiPart>
#include "network/HTTPClient.h"

struct ResponseCommonPart
{
    QString requestId;
    int timeUsed;
    QString errorMessage;
};

class FacePlusPlusHTTP: public HTTPClient
{
    Q_OBJECT

public:
    FacePlusPlusHTTP();
    ResponseCommonPart getResponseCommonPart() const;
    QString getLastError() const;

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
    ResponseCommonPart responseCommonPart;

    QFile* getPhotoFile(const QString& photoURL);
    virtual void addLoginPart(QHttpMultiPart* multiPart);


private:
    bool parsResponseCommonPart(const QJsonObject& jsonObject);
};

#endif // FACEPLUSPLUSHTTP_H
