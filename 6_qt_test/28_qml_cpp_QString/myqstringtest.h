#ifndef MYQSTRINGTEST_H
#define MYQSTRINGTEST_H

#include <QObject>
#include <stdio.h>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QFile>

#define here() cout << __FUNCTION__ << __LINE__ << endl;

class MyQstringTest : public QObject
{
    Q_OBJECT
public:
    explicit MyQstringTest(QObject *parent = nullptr);

    static void myQListIterator();      // static 方式不用创建实例，外部可直接使用
    static void myQlistJoin();
    static void myQstrintSplit();
    static void myQTextStream();
    static void mytrimmed();

signals:

public slots:
};

#endif // MYQSTRINGTEST_H
