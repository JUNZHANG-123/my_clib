#include "myobject.h"

static MyObject *m_obj = NULL;

MyObject::MyObject(QObject *parent) : QObject(parent)
{
}

QObject *MyObject::getInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    if (m_obj == NULL)
        m_obj = new MyObject();

    return m_obj;
}

MyObject *MyObject::getInstance()
{
    if (m_obj == NULL)
        m_obj = new MyObject();

    return m_obj;
}

void MyObject::func()
{
    emit cppSig(20, "wanwu");
    qDebug() << __FUNCTION__;
}

QString MyObject::sString() const
{
    return m_sString;
}

void MyObject::setSString(const QString &sString)
{
    m_sString = sString;
}

int MyObject::iValue() const
{
    return m_iValue;
}

void MyObject::setIValue(int iValue)
{
    m_iValue = iValue;
}
