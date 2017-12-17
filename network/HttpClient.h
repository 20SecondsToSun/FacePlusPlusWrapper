#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QSslError>
#include <QUrlQuery>
#include <QHttpPart>
#include <QHttpMultiPart>

class HTTPClient : public QObject
{
    Q_OBJECT

signals:
    void requestSuccessSignal(const QByteArray&);
    void requestFailSignal();

protected slots:
    virtual void httpRequestSuccessHandler(QNetworkReply* reply);
    void onSslError(QNetworkReply* reply,const QList<QSslError> &errors);

public:
    explicit HTTPClient(QObject *parent = nullptr);

    void setTimeout(int interval);
    void setRequestAttempts(int count);
    void makeRequest(const QString& url, QHttpMultiPart* multiPart);
    bool getRequestStatus() const;

private:
    void requestProxy(const QString& url, QHttpMultiPart *multiPart);
    void checkConnectionOntimer();
    void requestFailedPostAction();

    QString url;
    QNetworkAccessManager *networkManager;
    QTimer* timer;
    QNetworkReply* httpReply;

    int requestErrorCount = 0;
    bool requestInProgress = false;
    bool requestSucces = false;
    int MAX_REQUEST_COUNT = 1;
};

#endif // HTTPCLIENT_H
