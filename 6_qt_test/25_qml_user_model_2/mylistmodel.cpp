#include "mylistmodel.h"

MyListModel::MyListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_data.append(MyData("aaa", 1));            // 给 m_data 这个list 添加数据
    m_data.append(MyData("bbb", 11));
    m_data.append(MyData("ccc", 111));
}

MyListModel *MyListModel::getInstance()
{
    static MyListModel *obj = new MyListModel();
    return obj;
}

int MyListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return m_data.count();
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == MyRoleName::Name) {             // 相应的key 返回相应的值
        return m_data[index.row()].m_string;    // (0, 0) row index, column index
    } else if (role == MyRoleName::Value) {
        return m_data[index.row()].m_value;
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> MyListModel::roleNames() const
{
    QHash<int, QByteArray> roles;               // 完成映射
    roles.insert(MyRoleName::Name, "name");     // 字符串是QML 端要用的
    roles.insert(MyRoleName::Value, "value");   //枚举是c++ 来判断  看 data 函数
    return roles;
}

