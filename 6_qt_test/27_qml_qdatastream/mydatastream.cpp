#include <QDebug>
#include <QDataStream>
#include "mydatastream.h"

static void packEnableSysAutoOffScreenMsg(const bool val, QByteArray &netData)
{
    QDataStream out(&netData, QIODevice::ReadWrite);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out.setVersion(QDataStream::Qt_4_6);

    //设置发送长度初始值为0
    out << (quint8) 0xA0;
    out << (quint8) 0xFF;
    out << (quint8) 0xE1;
    out << (quint8) 0xD4;
    out << (quint8) val;
    out << (quint8) 0xFF;
    //回到字节流起始位置
    out.device()->seek(1);
    //重置字节流长度
    out << (quint8) (netData.size());

    qDebug() << netData.toHex();
}

static void printDataStream(QByteArray &Data)
{
    for(int i = 0; i < Data.size(); i++) {
        qDebug() << i << ": " << Data.at(i);
    }
}

myDataStream::myDataStream(QObject *parent) : QObject(parent)
{

}

void myDataStream::myTest()
{
    QByteArray bjson;
    packEnableSysAutoOffScreenMsg(true, bjson);
    qDebug()<<"sendEnableSysAutoOffScreen :" << bjson.toHex();

    printDataStream(bjson);
}




