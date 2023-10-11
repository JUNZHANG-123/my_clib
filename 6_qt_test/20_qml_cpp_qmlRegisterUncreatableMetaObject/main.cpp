#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "myobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 注册一个类型，qml 中不能创建实例，只能访问第五个参数访问枚举
    qmlRegisterUncreatableMetaObject(MyObject::staticMetaObject, "MyObj", 1, 0, "MyObject", "Access to enums & flags only");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
