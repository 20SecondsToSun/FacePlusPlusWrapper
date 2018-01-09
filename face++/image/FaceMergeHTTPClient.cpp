#include "FaceMergeHTTPClient.h"

#include <QFile>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>

FaceMergeHTTPClient::FaceMergeHTTPClient()
{
    connect(this, SIGNAL(requestFailSignal()), this, SLOT(requestFailedHandler()));
}

void FaceMergeHTTPClient::initService(const QString& settingsFile)
{
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("Server");
    FACE_MERGE_URL = settings.value("FACE_MERGE_PROTOCOL").toString()
            + "://" + settings.value("FACE_MERGE_HOST").toString()
            + "/" + settings.value("FACE_MERGE_METHOD").toString();

    API_KEY = settings.value("API_KEY").toString();
    API_SECRET = settings.value("API_SECRET").toString();
    FACE_SERVER_TIMEOUT = settings.value("FACE_SERVER_TIMEOUT").toInt();
    settings.endGroup();

    HTTPClient::setTimeout(FACE_SERVER_TIMEOUT);
    HTTPClient::setRequestAttempts(2);
}

void FaceMergeHTTPClient::sendPhoto(const QString& photoURL1, const QString& photoURL2)
{
    QFile* file1 = getPhotoFile(photoURL1);
    QFile* file2 = getPhotoFile(photoURL2);

    if(!file1->isOpen() || !file2->isOpen())
    {
        qDebug()<<"no file found";
        return;
    }

    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);


    QHttpPart imageTemplatePart;
    imageTemplatePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imageTemplatePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"template_file\"; filename=\"face1.jpeg\""));
    imageTemplatePart.setBodyDevice(file1);
    file1->setParent(multiPart);
    multiPart->append(imageTemplatePart);

    QHttpPart imageMergePart;
    imageMergePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imageMergePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"merge_file\"; filename=\"face1.jpeg\""));
    imageMergePart.setBodyDevice(file2);
    file1->setParent(multiPart);
    multiPart->append(imageMergePart);


    QHttpPart rectanglePart;
    rectanglePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"template_rectangle\""));
    rectanglePart.setBody("0,200,400,500");
    multiPart->append(rectanglePart);

    QHttpPart loginPart;
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"api_key\""));
    loginPart.setBody(API_KEY.toUtf8());
    multiPart->append(loginPart);

    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"api_secret\""));
    loginPart.setBody(API_SECRET.toUtf8());
    multiPart->append(loginPart);

}

QFile* FaceMergeHTTPClient::getPhotoFile(const QString& photoURL)
{
    QString cleanUrl = photoURL;
    QString prefix = "file:///";
    cleanUrl = cleanUrl.remove(0, prefix.size());

    QFile* file = new QFile(cleanUrl);
    file->open(QIODevice::ReadOnly);
    return file;
}

void FaceMergeHTTPClient::httpRequestSuccessHandler(QNetworkReply* reply)
{
    HTTPClient::httpRequestSuccessHandler(reply);

    auto data  = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonResponse.object();
    emit requestSuccessSignal(jsonObject);
}

void FaceMergeHTTPClient::requestFailedHandler()
{
    emit serviceErrorSignal();
}

