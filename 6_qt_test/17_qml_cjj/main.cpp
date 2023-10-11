#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include <QObject>
#include "myobect.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 全局对象  上下文对象 （内部有同名属性，则全局对象会被内部覆盖，跟c一样）
    // 通过c++ 端设置全局属性来给 qml 端使用
    QQmlContext* context = engine.rootContext();
    //QScreen *screen = QGuiApplication::primaryScreen();             // 获取屏幕属性
    //QRect rect = screen->virtualGeometry();                         // 获取屏幕宽度
    //context->setContextProperty("SCREEN_WIDTH", rect.width());      // SCREEN_WIDTH  为全局对象
    context->setContextProperty("SCREEN_WIDTH", 640);

    // 注册当前类型，在QML 中就可以访问，"MyObj" 是要引入的类名称，后面是版本号，最后是控件名
    qmlRegisterType<MyObect>("MyObj", 1, 0, "MyObect"); //我们一定要通过创建对象来定义一个我们自定义的object

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // engine 加载完成后，load 以后，对应示例1中： 3、c++ 端实现绑定信号和槽 ，查看 main.cpp
    auto list = engine.rootObjects();
    //auto objName = list.first()->objectName();
    //qDebug() << objName;
    //auto objBtn = list.first()->findChild<QObject *>("btn");    // 通过遍历方式找到对应控件
    //qDebug() << objBtn;
    auto win = list.first();
    // win 发送信号者；发送信号 SIGNAL 信号，注意命名，qml 中string 对应 c++中QString; 接收信号者：第三个绑定类实例； 最后一个接收槽函数
    //QObject::connect(win, SIGNAL(qmlSig(int, QString)), MyObect::getInstance(), SLOT(cppSlot(int, QString)) );

    return app.exec();
}
