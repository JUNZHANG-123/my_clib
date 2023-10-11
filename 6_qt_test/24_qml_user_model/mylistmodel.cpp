#include "mylistmodel.h"

MyListModel::MyListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_data.append("aaa");
    m_data.append("bbb");
    m_data.append("ccc");
}

// 建立映射
QHash<int, QByteArray> MyListModel::roleNames() const
{
    QHash<int, QByteArray> roles;               // 完成映射
    roles.insert(MyRoleName::Name, "name");     // 字符串是QML 端要用的
    roles.insert(MyRoleName::Value, "value");   // 枚举是c++ 来判断  看 data 函数
    return roles;
}

int MyListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return m_data.count();      // 返回当前数据有多少个
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    // (0, 0) row index, column index
    if (!index.isValid())
        return QVariant();

    if (role == MyRoleName::Name) {
        return m_data[index.row()];
    }

    // FIXME: Implement me!
    return QVariant();
}

MyListModel *MyListModel::getInstance()
{
    static MyListModel *obj = new MyListModel();
    return obj;
}
