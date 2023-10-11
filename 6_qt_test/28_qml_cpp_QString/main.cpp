#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "myqstringtest.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // my test start

    //MyQstringTest::myQListIterator();
    //MyQstringTest::myQlistJoin();
    //MyQstringTest::myQstrintSplit();
    //MyQstringTest::myQTextStream();
    MyQstringTest::mytrimmed();

    // my test end


    return app.exec();
}
