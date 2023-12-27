#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "myqstringtest.h"
#include <QJsonObject>

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

    qDebug() << QString("process%1").arg(0);
    QJsonObject info;

    int data = 2;
    info.insert(QString("progress%1").arg(1), QVariant(data).toJsonValue());
    info.insert(QString("curIndex%1").arg(1), QVariant(data).toJsonValue());

    info.insert(QString("progress%1").arg(1), QVariant(20).toJsonValue());

    QJsonObject info2;
    info2 = info;
    info2.insert(QString("progress%1").arg(20), QVariant(10).toJsonValue());
    info2.insert(QString("curIndex%1").arg(2), QVariant(data).toJsonValue());

    qDebug() << info2 << info2.find( QString("progress%1").arg(2) )->isUndefined();

    qDebug() << info2.contains(QString("progress%1").arg(1)) ;

    qDebug() << info2[QString("progress%1").arg(1)].toInt() ;

    return app.exec();
}
