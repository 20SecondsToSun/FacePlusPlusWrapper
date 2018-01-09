#ifndef BODYCONTROLLER_H
#define BODYCONTROLLER_H

#include <QObject>
#include <QString>
#include "face++/Controller.h"
#include "BodyDetectionHTTPClient.h"
#include "../FacePlusPlusConfig.h"
#include "BodyDetectionParser.h"
#include "BodySegmentDetectionParser.h"
#include "BodyGestureDetectionParser.h"

class BodyController : public Controller
{
    Q_OBJECT
public:
    explicit BodyController(QObject *parent = nullptr);

    virtual ~BodyController();

    virtual void init() override;
    Q_INVOKABLE virtual void run(const QString& path) override;

private:
    BodyDetectionHTTPClient* bodyDetectionHTTPClient;
    FacePlusPlusConfig* config;

public slots:
    void httpErrorHandler();
    void requestSuccessHandler(const QJsonObject& jsonObject);
};

#endif // BODYCONTROLLER_H
