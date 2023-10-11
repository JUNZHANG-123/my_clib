#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto list = engine.rootObjects();
    auto win = list.first();

    QVariant ret;
    QVariant arg_1 = 123;
    QVariant arg_2 = "zhangsan";
    //使用该接口调用qml 端函数，第一个参数，调用对象; 第二个参数，调用函数接口；第三个参数，返回值；第4个开始是函数参数，可以多个；
    // qml 端参数和返回值都是 QVariant 类型
    QMetaObject::invokeMethod(win, "qmlFunc", Q_RETURN_ARG(QVariant, ret), Q_ARG(QVariant, arg_1), Q_ARG(QVariant, arg_2));

    qDebug() << "ret" << ret;
    return app.exec();
}
