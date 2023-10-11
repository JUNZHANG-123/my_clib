import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    width: 200
    height: 100
    color: "black"

    //property int testValue: 0       // 定义在这相当于 public

    QtObject {
        id: attributes                // 外部要访问可以给这个控件取别名
        property int testValue: 0     // 定义在这相当于 private
    }

    Component.onCompleted: {
        console.log(attributes.testValue)       // 可以用 attributes.testValue 放松访问 property int testValue
    }

    property alias attr: attributes   // 给 attributes 取别名后，外部可以通过 attr 访问(获取/设置)
}
