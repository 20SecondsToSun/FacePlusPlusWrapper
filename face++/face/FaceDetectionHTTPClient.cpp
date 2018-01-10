#include "FaceDetectionHTTPClient.h"

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

    HTTPClient::setTimeout(FACE_SERVER_TIMEOUT);
    HTTPClient::setRequestAttempts(2);
}

void FaceDetectionHTTPClient::sendPhoto(const QString& photoURL)
{
    QFile* file = getPhotoFile(photoURL);

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

    addLoginPart(multiPart);

    QHttpPart attrPart;
    attrPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"return_landmark\""));
    attrPart.setBody("1");
    multiPart->append(attrPart);

    attrPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"return_attributes\""));
    attrPart.setBody(RETURN_ATTRIBUTES.toUtf8());
    multiPart->append(attrPart);

    makeRequest(FACE_URL, multiPart);
}
