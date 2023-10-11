#ifndef MYOBECT_H
#define MYOBECT_H

#include <QObject>
#include <QDebug>

class MyObect : public QObject
{
    Q_OBJECT

    // type 变量类型，name 变量名称，READ name 通过哪个接口读值， WRITE 通过哪个接口设置值，NOTIFY nameChanged 值改变后通过哪个接口发送信号
    //Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)

    //Q_PROPERTY(int iValue READ iValue WRITE setIValue NOTIFY iValueChanged)
    //Q_PROPERTY(QString sString READ sString WRITE setSString NOTIFY sStringChanged)

    Q_PROPERTY(int iValue MEMBER m_iValue NOTIFY iValueChanged)             // 用 MEMBER m_iValue 设置成员变量和上面设置 READ iValue WRITE setIValue  效果一样
    Q_PROPERTY(QString sString MEMBER m_sString NOTIFY sStringChanged)
public:
    explicit MyObect(QObject *parent = nullptr);

    int iValue() const;
    void setIValue(int newIValue);

    QString sString() const;
    void setSString(const QString &sString);

    Q_INVOKABLE void func();        // 加 Q_INVOKABLE 后，该函数在QML 中就可以调用

    static MyObect *getInstance();

private:
    int m_iValue;
    QString m_sString;

signals:
    void iValueChanged();
    void sStringChanged();

    void cppSig(int i, QString s);  // 信号

public slots:
    void cppSlot(int i, QString s); // 定义槽函数
};

#endif // MYOBECT_H
