#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>
#include <QHash>

class MyListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MyRoleName {
        Name = Qt::DisplayRole + 1,
        Value
    };

    explicit MyListModel(QObject *parent = nullptr);

    // 建立c++ 和qml 映射， 字符串和枚举的映射，枚举c++定义即key，字符串，qml中使用
    // hash 键值对，QHash<int 枚举， QByteArray 值
    QHash<int, QByteArray> roleNames() const override;

    // Basic functionality:
    // 元素个数或者 model 大小/长度, 其他控件可能还有 columnCount
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // key 对应数据内容返回的具体实现
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static MyListModel *getInstance();

private:
    QList<QString> m_data;      // 数据来源，建立一个list 数据类似是 QString

};

#endif // MYLISTMODEL_H
