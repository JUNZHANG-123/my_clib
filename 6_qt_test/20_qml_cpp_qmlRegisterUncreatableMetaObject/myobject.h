#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
    Q_ENUMS(MyEnum)         // 声明该枚举在qml 中使用
    Q_PROPERTY(int iValue MEMBER m_iValue NOTIFY iValueChanged)

public:
    explicit MyObject(QObject *parent = nullptr);
    int m_iValue;

    enum MyEnum {           // 第一个字母一定要大写，包括枚举中的变量
        Key1,
        Key2,
    };

    int iValue() const;
    void setIValue(int iValue);

    Q_INVOKABLE void func();        // 加 Q_INVOKABLE 后，该函数在QML 中就可以调用

signals:
    void iValueChanged();

public slots:
};

#endif // MYOBJECT_H
