#ifndef FACECONTROLLER_H
#define FACECONTROLLER_H

#include <QObject>
#include <QString>
#include "face++/Controller.h"
#include "FaceDetectionHTTPClient.h"
#include "../FacePlusPlusConfig.h"
#include "FaceDetectionParser.h"

class FaceController : public Controller
{
    Q_OBJECT
public:
    explicit FaceController(QObject *parent = nullptr);
    virtual ~FaceController();

    virtual void init() override;
    Q_INVOKABLE virtual void run(const QString& path) override;

private:
    FaceDetectionHTTPClient* faceDetectionHTTPClient;
    FacePlusPlusConfig* config;

signals:

public slots:
    void httpErrorHandler();
    void requestSuccessHandler(const QJsonObject& jsonObject);

};

#endif // FACECONTROLLER_H
