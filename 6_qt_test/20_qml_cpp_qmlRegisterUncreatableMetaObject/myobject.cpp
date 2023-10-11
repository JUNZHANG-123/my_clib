#include "myobject.h"
#include <QDebug>

MyObject::MyObject(QObject *parent) : QObject(parent)
{

}

int MyObject::iValue() const
{
    return m_iValue;
}

void MyObject::setIValue(int iValue)
{
    m_iValue = iValue;
}

void MyObject::func()
{
    qDebug() << __FUNCTION__;
}
