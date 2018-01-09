#include "BodyDetectionHTTPClient.h"

#include <QFile>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>

BodyDetectionHTTPClient::BodyDetectionHTTPClient()
{
    connect(this, SIGNAL(requestFailSignal()), this, SLOT(requestFailedHandler()));
}

void BodyDetectionHTTPClient::initService(const QString& settingsFile)
{
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("Server");
    BODY_URL = settings.value("BODY_PROTOCOL").toString()
            + "://" + settings.value("BODY_HOST").toString()
            + "/" + settings.value("BODY_METHOD").toString();

    BODY_SEGMENT_URL = settings.value("BODY_PROTOCOL").toString()
            + "://" + settings.value("BODY_HOST").toString()
            + "/" + settings.value("BODY_SEGMENT_METHOD").toString();

    BODY_GESTURE_URL = settings.value("BODY_PROTOCOL").toString()
            + "://" + settings.value("BODY_HOST").toString()
            + "/" + settings.value("BODY_GESTURE_METHOD").toString();

    API_KEY = settings.value("API_KEY").toString();
    API_SECRET = settings.value("API_SECRET").toString();
    FACE_SERVER_TIMEOUT = settings.value("FACE_SERVER_TIMEOUT").toInt();
    settings.endGroup();

    HTTPClient::setTimeout(FACE_SERVER_TIMEOUT);
    HTTPClient::setRequestAttempts(2);
}

void BodyDetectionHTTPClient::sendPhoto(const QString& photoURL, BODY_REQUEST_TYPE type)
{
    QString cleanUrl = photoURL;
    QString prefix = "file:///";
    cleanUrl = cleanUrl.remove(0, prefix.size());

    QFile* file = new QFile(cleanUrl);
    file->open(QIODevice::ReadOnly);

    if(!file->isOpen())
    {
        qDebug()<<"no file found";
        return;
    }

    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image_file\"; filename=\"face1.jpeg\""));
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(imagePart);

    QHttpPart loginPart;
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"api_key\""));
    loginPart.setBody(API_KEY.toUtf8());
    multiPart->append(loginPart);

    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"api_secret\""));
    loginPart.setBody(API_SECRET.toUtf8());
    multiPart->append(loginPart);

    switch(type)
    {
        case BODY_REQUEST_TYPE::BODY_DETECT:
        {
            QHttpPart attrPart;
            attrPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"return_attributes\""));
            attrPart.setBody(RETURN_ATTRIBUTES.toUtf8());
            multiPart->append(attrPart);
            makeRequest(BODY_URL, multiPart);
        }
        break;

        case BODY_REQUEST_TYPE::SEGMENT:
            makeRequest(BODY_SEGMENT_URL, multiPart);
        break;

        case BODY_REQUEST_TYPE::GESTURE:
            makeRequest(BODY_GESTURE_URL, multiPart);
        break;
    }

}

void BodyDetectionHTTPClient::httpRequestSuccessHandler(QNetworkReply* reply)
{
    HTTPClient::httpRequestSuccessHandler(reply);

    auto data  = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonResponse.object();
    emit requestSuccessSignal(jsonObject);
}

void BodyDetectionHTTPClient::requestFailedHandler()
{
    emit serviceErrorSignal();
}
