#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "myobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 全局单例例子，实现后 qml 类中可以直接用类名访问
    // 单例的好处是不用在qml 创建该obj
    qmlRegisterSingletonType<MyObject>("MyObj", 1, 0, "MyObject", MyObject::getInstance);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto list = engine.rootObjects();
    auto win = list.first();
    // 接收槽函数在qml 中，那么对应的C++注册信号函数中的传参类型都是 QVariant
    QObject::connect(MyObject::getInstance(), SIGNAL(cppSig(QVariant, QVariant)), win, SLOT(myqmlSolt(QVariant, QVariant)) );

    return app.exec();
}
