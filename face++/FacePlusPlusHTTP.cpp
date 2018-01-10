#include "FacePlusPlusHTTP.h"
#include <QJsonDocument>
#include <QJsonObject>

FacePlusPlusHTTP::FacePlusPlusHTTP()
{

}

QFile* FacePlusPlusHTTP::getPhotoFile(const QString& photoURL)
{
    QString cleanUrl = photoURL;
    QString prefix = "file:///";
    cleanUrl = cleanUrl.remove(0, prefix.size());

    QFile* file = new QFile(cleanUrl);
    file->open(QIODevice::ReadOnly);
    return file;
}

void FacePlusPlusHTTP::httpRequestSuccessHandler(QNetworkReply* reply)
{
    HTTPClient::httpRequestSuccessHandler(reply);
    auto data  = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonResponse.object();
    emit requestSuccessSignal(jsonObject);
}

void FacePlusPlusHTTP::requestFailedHandler()
{
    emit serviceErrorSignal();
}

void FacePlusPlusHTTP::addLoginPart(QHttpMultiPart* multiPart)
{
    QHttpPart loginPart;
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"api_key\""));
    loginPart.setBody(API_KEY.toUtf8());
    multiPart->append(loginPart);

    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"api_secret\""));
    loginPart.setBody(API_SECRET.toUtf8());
    multiPart->append(loginPart);
}

