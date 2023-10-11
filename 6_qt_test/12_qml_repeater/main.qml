import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Repeater {
//        model: 3        // 模型 可是各种类型，如果是数字的话，表示有几个控件。表示要循环几次
//        Rectangle {
//            y: index*50                 // 更加index 修改位置
//            width: 100; height: 40
//            border.width: 1
//            color: "yellow"
//        }

        model: ["Button", "Rectangle", "MouseArea"]     // 数量是3，读取list 大小，数据可以被下面控件使用
        Button {
            y: index*50
            width: 200; height: 40
            text: modelData + " " + index                           // 使用 modelData
        }
        Component.onCompleted: console.log(count)
    }



}
