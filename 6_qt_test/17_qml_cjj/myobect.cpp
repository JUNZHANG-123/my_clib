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


/*
static MyObect m_obj;
1、它需要加载时初始化MyType（即MyType加载库或应用程序时调用的默认构造函数）;
2、即使从未使用过，类型也会被初始化;
3、不同的单元之间的初始化和破坏的顺序不确定，导致在初始化之前或销毁之后可能会使用;
4、如果它是在一个函数内（即不是全局的）发现的，它将在第一次使用时被初始化，但是许多当前编译器中并不保证初始化是线程安全的;

Q_GLOBAL_STATIC宏通过在第一次使用时保证线程安全初始化并允许用户查询类型是否已被销毁以避免销毁后使用问题来解决上述所有问题。

注意：如果要使用该宏，那么累的构造函数和析构函数必须是公有的才行，如果构造函数和析构函数是私有或者受保护的类型，是不能使用该宏的。
*/
Q_GLOBAL_STATIC(MyObect, m_obj)
MyObect *MyObect::getInstance()
{
//    static MyObect *obj = new MyObect();
//    return obj;
    return m_obj;
}

void MyObect::cppSlot(int i, QString s)
{
    qDebug() << __FUNCTION__ << "i " << i << "s " <<s;
}

