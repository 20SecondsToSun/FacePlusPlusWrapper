#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QBuffer>
#include <QImageReader>
#include <QRect>
#include <QVector>
#include <QQuickItem>
#include <QApplication>

#include "config/Config.h"
#include "face++/face/FaceTypes.h"
#include "face++/face/FaceDetectionHTTPClient.h"

class Controller : public QObject
{
    Q_OBJECT

signals:
    void faceNotFound();
    void httpError();
    void newFaceData(const Face& face);

public:
    Controller();
    void init(Config* config);

    Q_INVOKABLE void run();

public slots:
    void faceRecognitionHandler(const QVector<Face>& faces);
    void httpErrorHandler();
    void faceNotFoundHandler();

private:
    FaceDetectionHTTPClient* faceDetectionHTTPClient;
};

#endif // CONTROLLER_H
