#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "downloadmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    DownloadManager d_manager;
    d_manager.startDownload();

    return app.exec();
}
