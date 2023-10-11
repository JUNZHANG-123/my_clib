#include "myobect.h"

MyObect::MyObect(QObject *parent) : QObject(parent)
{

}

int MyObect::iValue() const
{
    qDebug() << __FUNCTION__;
    return m_iValue;
}

void MyObect::setIValue(int newIValue)
{
    if (m_iValue == newIValue)
        return;

    qDebug() << __FUNCTION__ << newIValue;
    m_iValue = newIValue;
    emit iValueChanged();
}

QString MyObect::sString() const
{
    return m_sString;
}

void MyObect::setSString(const QString &newString)
{
    if (m_sString == newString)
        return;

    m_sString = newString;
    emit sStringChanged();
}

void MyObect::func()
{
    emit cppSig(20, "wanwu");
    qDebug() << __FUNCTION__;
}

MyObect *MyObect::getInstance()
{
    static MyObect *obj = new MyObect();
    return obj;
}

void MyObect::cppSlot(int i, QString s)
{
    qDebug() << __FUNCTION__ << "i " << i << "s " <<s;
}

