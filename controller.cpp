#include "controller.h"

Controller::Controller()
{
}

void Controller::init(Config* config)
{
    faceDetectionHTTPClient = new FaceDetectionHTTPClient();
    faceDetectionHTTPClient->initService(config->getSettingsFile());
    connect(faceDetectionHTTPClient, SIGNAL(serviceErrorSignal()), this, SLOT(httpErrorHandler()));
    connect(faceDetectionHTTPClient, SIGNAL(faceNotFoundSignal()), this, SLOT(faceNotFoundHandler()));
    connect(faceDetectionHTTPClient, SIGNAL(faceRecognizedSignal(const QVector<Face>&)), this, SLOT(faceRecognitionHandler(const QVector<Face>&)));
}

void Controller::httpErrorHandler()
{   
    emit httpError();
}

void Controller::faceNotFoundHandler()
{   
    emit faceNotFound();
}

void Controller::faceRecognitionHandler(const QVector<Face>& faces)
{
    //emit newFaceData(faces);
}

void Controller::run()
{
    faceDetectionHTTPClient->sendPhoto("path");
}

