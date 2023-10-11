import QtQml.Models 2.2
import QtQuick 2.0

Rectangle {
    id: bordorRect
    width: 200
    height: 100
    color: "red"

//// 配合示例2 使用
//    property Component mycom
//    Loader {
//        id: loader
//        sourceComponent: mycom
//    }


//// 配合示例 7
    property alias newInnerRect: inner      // 给控件或者属性取别名
    property alias newInnerRectColor: inner.color
    Rectangle {
        id: inner
        width: 50
        height: 50
        anchors.centerIn: parent
        color: "black"
    }
}
