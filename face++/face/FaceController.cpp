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

    connect(faceDetectionHTTPClient, SIGNAL(faceRecognizedSignal(const QVector<Face>&)), this, SLOT(faceRecognitionHandler(const QVector<Face>&)));
    connect(faceDetectionHTTPClient, SIGNAL(serviceErrorSignal()), this, SLOT(httpErrorHandler()));
    connect(faceDetectionHTTPClient, SIGNAL(faceNotFoundSignal()), this, SLOT(faceNotFoundHandler()));
}

void FaceController::run(const QString& path)
{
    faceDetectionHTTPClient->sendPhoto(path);
}

void FaceController::faceRecognitionHandler(const QVector<Face>& faces)
{

}

void FaceController::httpErrorHandler()
{

}

void FaceController::faceNotFoundHandler()
{

}

FaceController::~FaceController()
{
    delete faceDetectionHTTPClient;
    delete config;
}



