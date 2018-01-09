#ifndef FACEMERGECONTROLLER_H
#define FACEMERGECONTROLLER_H

#include <QObject>
#include <QString>
#include "face++/Controller.h"
#include "FaceMergeHTTPClient.h"
#include "../FacePlusPlusConfig.h"
#include "FaceMergeParser.h"

class FaceMergeController : public Controller
{
    Q_OBJECT
public:
    explicit FaceMergeController(QObject *parent = nullptr);
    virtual ~FaceMergeController();

    virtual void init() override;
    Q_INVOKABLE virtual void run(const QString& path1, const QString& path2) override;

private:
    FaceMergeHTTPClient* faceMergeHTTPClient;
    FacePlusPlusConfig* config;

public slots:
    void httpErrorHandler();
    void requestSuccessHandler(const QJsonObject& jsonObject);
};

#endif // FACEMERGECONTROLLER_H
