#include "FaceDetectionHTTPClient.h"
#include "FaceDetectionParser.h"
#include <QFile>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>

FaceDetectionHTTPClient::FaceDetectionHTTPClient()
{
    connect(this, SIGNAL(requestFailSignal()), this, SLOT(requestFailedHandler()));
}

void FaceDetectionHTTPClient::initService(const QString& settingsFile)
{
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("Server");
    FACE_URL = settings.value("FACE_PROTOCOL").toString()
            + "://" + settings.value("FACE_HOST").toString()
            + "/" + settings.value("FACE_METHOD").toString();

    API_KEY = settings.value("API_KEY").toString();
    API_SECRET = settings.value("API_SECRET").toString();
    FACE_SERVER_TIMEOUT = settings.value("FACE_SERVER_TIMEOUT").toInt();
    settings.endGroup();

    setTimeout(FACE_SERVER_TIMEOUT);
    setRequestAttempts(2);
}

void FaceDetectionHTTPClient::sendPhoto(const QString& photoURL)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image_file\"; filename=\"face1.jpeg\""));

    QFile* file = new QFile(photoURL);
    file->open(QIODevice::ReadOnly);
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

    QHttpPart attrPart;
    attrPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"return_landmark\""));
    attrPart.setBody("1");
    multiPart->append(attrPart);

    attrPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"return_attributes\""));
    attrPart.setBody("headpose,gender,eyegaze,beauty");
    multiPart->append(attrPart);

    makeRequest(FACE_URL, multiPart);
}

void FaceDetectionHTTPClient::httpRequestSuccessHandler(QNetworkReply* reply)
{
    HTTPClient::httpRequestSuccessHandler(reply);
    auto data  = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonResponse.object();

    FaceDetectionParcer parser;
    parser.parse(jsonObject);

    if(parser.noFaces())
    {
        emit faceNotFoundSignal();
    }
    else
    {
        emit faceRecognizedSignal(parser.getFaces());
    }
}

void FaceDetectionHTTPClient::requestFailedHandler()
{
    emit serviceErrorSignal();
}
