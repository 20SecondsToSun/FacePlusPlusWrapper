#include "FaceController.h"

#include <QDebug>

FaceController::FaceController(QObject *parent) : Controller(parent)
{

}

void FaceController::init()
{
    config = new FacePlusPlusConfig();

    faceDetectionHTTPClient = new FaceDetectionHTTPClient();
    faceDetectionHTTPClient->initService(config->getSettingsFile());

    connect(faceDetectionHTTPClient, SIGNAL(serviceErrorSignal()), this, SLOT(httpErrorHandler()));
    connect(faceDetectionHTTPClient, SIGNAL(requestSuccessSignal(const QJsonObject&)), this, SLOT(requestSuccessHandler(const QJsonObject&)));
}

void FaceController::run(const QString& path)
{
    faceDetectionHTTPClient->sendPhoto(path);
}

void FaceController::requestSuccessHandler(const QJsonObject& jsonObject)
{
    FaceDetectionParcer parser;
    parser.parse(jsonObject);

    if(parser.noFaces())
    {
        qDebug()<<"no faces";
    }
    else
    {
        qDebug()<<"find faces count: "<< parser.getFaces().size();
    }
}

void FaceController::httpErrorHandler()
{

}

FaceController::~FaceController()
{
    delete faceDetectionHTTPClient;
    delete config;
}
