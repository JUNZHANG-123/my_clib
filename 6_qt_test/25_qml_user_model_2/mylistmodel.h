#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>

struct MyData {                 // 定义结构体，c++中结构体跟 class 一样
    MyData(QString s, int v) {  // 构造函数中赋值
        m_string = s;
        m_value = v;
    }

//    MyData(QString s, int v): m_string(s),m_value(v) {}       // 使用初始化列表方式赋值
    QString m_string;
    int m_value;
};

class MyListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MyRoleName {
        Name = Qt::DisplayRole + 1,
        Value
    };

    explicit MyListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //
    QHash<int,QByteArray> roleNames() const override;

    static MyListModel *getInstance();

private:
    QList<MyData> m_data;
};

#endif // MYLISTMODEL_H
