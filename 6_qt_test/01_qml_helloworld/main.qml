import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true                           // 是否可见，默认false
    width: 640
    height: 480
    objectName: "mainWin"                   // 控件名称
    color: "white"                          // 控件颜色
    title: qsTr("Hello World")
    x: 200                                  // 相对于父控件偏移
    y: 200

    function func () {
        let ret = 1,
        ret2 = 2,
        ret3 = 3;
        console.log(ret)

    }

    minimumWidth: 400                       // 最小宽度
    minimumHeight: 300
    maximumWidth: 600                       // 最大宽度，设置和最小一样则固定
    maximumHeight: 300

    opacity: 1                              // 0-1 透明度

    // 自定义信号+槽函数
    signal  mysig()                         // 信号
    onMysig: {                              // 槽函数, on+名称首字母大写

    }

    // 系统信号槽函数，任何控件的属性都会有相应的信号和槽函数
    onWidthChanged: {                       // 宽度改变则触发
        console.log("width:", width)        // 打印接口 console.log
    }

    // 自定义属性也会生存相应的信号和槽函数
    property int myValue: 3
    onMyValueChanged: {

    }


    Button {
        id: btn1
        objectName: "btn1"
        width: 50
        height: 50
        focus: true
        background: Rectangle {
            border.color: btn1.focus ? "blue" : "black"         // border 边框
        }
        onClicked: {
            console.log("btn1")
        }

        Keys.onRightPressed: {                                  // 右键 切换焦点
            btn2.focus = true
        }
    }

    Button {
        id: btn2
        objectName: "btn2"                                     // obj 名称
        width: 50
        height: 50
        x: 100
        background: Rectangle {
            border.color: btn2.focus ? "blue" : "black"
        }
        onClicked: {
            console.log("btn2")
        }

        Keys.onLeftPressed: {                                   // 左键 切换焦点
            btn1.focus = true
        }
    }

    onActiveFocusItemChanged: {                                 // 焦点切换后响应
        console.log("active focus item changed:", activeFocusItem, "obj name:", activeFocusItem.objectName)

    }



}














