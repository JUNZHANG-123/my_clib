#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "bleconnect.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<BLEConnect>("BleConnect.module",1,0,"BLE");
    qmlRegisterSingletonType(QUrl("qrc:/Common/Skin.qml"), "Skin", 1, 0, "Skin");
    qmlRegisterSingletonType(QUrl("qrc:/Common/Config.qml"), "Config", 1, 0, "Config");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
