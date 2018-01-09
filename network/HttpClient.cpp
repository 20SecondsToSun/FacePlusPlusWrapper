#include "HTTPClient.h"

HTTPClient::HTTPClient(QObject *parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestSuccessHandler(QNetworkReply*)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), this, SLOT(onSslError(QNetworkReply*, QList<QSslError>)));
}

void HTTPClient::setTimeout(int interval)
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkConnectionOnTimer()));
}

void HTTPClient::setRequestAttempts(int count)
{
    MAX_REQUEST_COUNT = count;
}

void HTTPClient::makeRequest(const QString& url, QHttpMultiPart* multiPart)
{

    requestErrorCount = 0;
    requestProxy(url, multiPart);
}

void HTTPClient::requestProxy(const QString& url, QHttpMultiPart* multiPart)
{
    qDebug() << "requestProxy " << url;
    this->url = url;
    requestInProgress = true;
    timer->start();

    QNetworkRequest request = QNetworkRequest(QUrl(url));
    QNetworkReply* httpReply = networkManager->post(request, multiPart);
    multiPart->setParent(httpReply);
}

void HTTPClient::onSslError(QNetworkReply* reply, const QList<QSslError>& errors)
{
    foreach (const QSslError &e, errors)
    {
        qDebug() << "SSL Error:" << e.errorString();
    }

    reply->ignoreSslErrors(errors);
}

void HTTPClient::checkConnectionOnTimer()
{
    if(requestInProgress && httpReply)
    {
        httpReply->abort();
    }
}

void HTTPClient::httpRequestSuccessHandler(QNetworkReply* reply)
{
    timer->stop();
    requestInProgress = false;

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Request failed, " << reply->errorString();
        requestFailedPostAction();
        reply->deleteLater();
    }
    else
    {
        requestErrorCount = 0;
        requestSucces = true;
    }
}

void HTTPClient::requestFailedPostAction()
{
    if(++requestErrorCount < MAX_REQUEST_COUNT)
    {
        qDebug()<<"request failed, try again "<<url;
        //todo repeat
       // requestProxy(url);
    }
    else
    {
        qDebug()<<"request failed, we tried several times((( ";
        requestErrorCount = 0;
        requestSucces = false;
        emit requestFailSignal();
    }
}

bool HTTPClient::getRequestStatus() const
{
    return requestSucces;
}
