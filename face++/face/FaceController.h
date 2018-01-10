#ifndef FACECONTROLLER_H
#define FACECONTROLLER_H

#include <QObject>
#include <QString>
#include "face++/Controller.h"
#include "FaceDetectionHTTPClient.h"
#include "../FacePlusPlusConfig.h"
#include "FaceDetectionParser.h"
#include "FaceCompareParcer.h"

class FaceController : public Controller
{
    Q_OBJECT
public:
    explicit FaceController(QObject *parent = nullptr);
    virtual ~FaceController();

    virtual void init() override;
    Q_INVOKABLE virtual void run(const QString& path) override;
    Q_INVOKABLE virtual void run(const QString& path1, const QString& path2) override;

private:
    FaceDetectionHTTPClient* faceDetectionHTTPClient;
    FacePlusPlusConfig* config;
    FACE_API_METHOD apiMethod;

signals:

public slots:
    void httpErrorHandler();
    void requestSuccessHandler(const QJsonObject& jsonObject);

};

#endif // FACECONTROLLER_H
