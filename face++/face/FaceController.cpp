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
    apiMethod = FACE_API_METHOD::DETECT;
    faceDetectionHTTPClient->faceDetect(path);
}

void FaceController::run(const QString& path1, const QString& path2)
{
    apiMethod = FACE_API_METHOD::COMPARE;
    faceDetectionHTTPClient->faceCompare(path1, path2);
}

void FaceController::requestSuccessHandler(const QJsonObject& jsonObject)
{
    if(apiMethod == FACE_API_METHOD::DETECT)
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
    else if(apiMethod == FACE_API_METHOD::COMPARE)
    {
        FaceCompareParcer parser;
        parser.parse(jsonObject);
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
