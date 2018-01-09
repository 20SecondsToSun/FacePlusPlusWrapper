#include "FaceMergeController.h"

FaceMergeController::FaceMergeController(QObject *parent) : Controller(parent)
{

}

void FaceMergeController::init()
{
    config = new FacePlusPlusConfig();

    faceMergeHTTPClient = new FaceMergeHTTPClient();
    faceMergeHTTPClient->initService(config->getSettingsFile());

    connect(faceMergeHTTPClient, SIGNAL(serviceErrorSignal()), this, SLOT(httpErrorHandler()));
    connect(faceMergeHTTPClient, SIGNAL(requestSuccessSignal(const QJsonObject&)), this, SLOT(requestSuccessHandler(const QJsonObject&)));
}

void FaceMergeController::run(const QString& path1, const QString& path2)
{
    faceMergeHTTPClient->sendPhoto(path1, path2);
}

void FaceMergeController::requestSuccessHandler(const QJsonObject& jsonObject)
{
    FaceMergeParser parser;
    parser.parse(jsonObject);
}

void FaceMergeController::httpErrorHandler()
{

}

FaceMergeController::~FaceMergeController()
{
    delete faceMergeHTTPClient;
    delete config;
}
