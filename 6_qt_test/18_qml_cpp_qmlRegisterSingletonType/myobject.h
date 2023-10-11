#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QDebug>

class MyObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int iValue MEMBER m_iValue NOTIFY iValueChanged)             // 用 MEMBER m_iValue 设置成员变量和上面设置 READ iValue WRITE setIValue  效果一样
    Q_PROPERTY(QString sString MEMBER m_sString NOTIFY sStringChanged)
    Q_ENUMS(MyEnum)

public:
    explicit MyObject(QObject *parent = nullptr);

    int m_iValue;
    QString m_sString;


    int iValue() const;
    void setIValue(int iValue);

    QString sString() const;
    void setSString(const QString &sString);

    static QObject* getInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    static MyObject* getInstance();

    Q_INVOKABLE void func();        // 加 Q_INVOKABLE 后，该函数在QML 中就可以调用

    enum MyEnum {           // 第一个字母一定要大写，包括枚举中的变量
        Key1,
        Key2,
    };

private:


signals:
    void iValueChanged();
    void sStringChanged();

    void cppSig(QVariant i, QVariant s);  // 信号

public slots:
};

#endif // MYOBJECT_H
