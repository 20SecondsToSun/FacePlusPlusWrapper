#include "BodyController.h"

BodyController::BodyController(QObject *parent) : Controller(parent)
{

}

void BodyController::init()
{
    config = new FacePlusPlusConfig();

    bodyDetectionHTTPClient = new BodyDetectionHTTPClient();
    bodyDetectionHTTPClient->initService(config->getSettingsFile());

    connect(bodyDetectionHTTPClient, SIGNAL(serviceErrorSignal()), this, SLOT(httpErrorHandler()));
    connect(bodyDetectionHTTPClient, SIGNAL(requestSuccessSignal(const QJsonObject&)), this, SLOT(requestSuccessHandler(const QJsonObject&)));
}

void BodyController::run(const QString& path)
{
    bodyDetectionHTTPClient->sendPhoto(path, BODY_REQUEST_TYPE::GESTURE);
}

void BodyController::requestSuccessHandler(const QJsonObject& jsonObject)
{
    qDebug()<<"jsonObject "<<jsonObject;
    BodyGestureDetectionParser parser;
    parser.parse(jsonObject);
   // parser.saveBodyGrayScale(qApp->applicationDirPath() + "/content/grayscale.jpg");
}

void BodyController::httpErrorHandler()
{

}

BodyController::~BodyController()
{
    delete bodyDetectionHTTPClient;
    delete config;
}
