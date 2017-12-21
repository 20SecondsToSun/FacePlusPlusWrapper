#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "config/Config.h"
#include "datamanager/DataManager.h"
#include "face++/face/FaceController.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QScopedPointer<Config> config(new Config);
    config->load();

    QScopedPointer<DataManager> dataManager(new DataManager);

    QScopedPointer<Controller> facecontroller(new FaceController);
    facecontroller->init();

    engine.rootContext()->setContextProperty("facecontroller", facecontroller.data());
    engine.rootContext()->setContextProperty("dataManager", dataManager.data());



    return app.exec();
}
