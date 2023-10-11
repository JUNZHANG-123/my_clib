import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、focus 基本介绍
//    Button {
//        id: btn
//        width: 100
//        height: 50
//        //focusPolicy: Qt.NoFocus                             // 设置为 Qt.NoFocus 则无法获取焦点，但是还是可以通过 forceActiveFocus()  设置焦点
//        background: Rectangle {
//            anchors.fill: parent
//            border.color: btn.focus ? "blue":"red"
//        }
//        onFocusChanged: {
//            console.log("focus:", focus)
//        }
//        onFocusReasonChanged: {
//            console.log("focus reason: ", focusReason)      // 获取 focus 原因
//        }
//        Component.onCompleted: {
//            console.log("focusPolicy:", focusPolicy)        // Qt.StrongFocus 11 这个按键会在按下或者使用tab 键时获取焦点
//        }
//    }

//// 2、多个控件同时获取 focus ，后构造的focus 会获取到焦点；文件后面的控件会先构造，比如下面 txt2 会先构造
//    Rectangle {
//        id: rect
//        width: 300
//        height: 200
//        Text {
//            id: txt1
//            focus: true
//            text: qsTr("text1: " +txt1.focus + " activeFocus1: "+ txt1.activeFocus)
//            Component.onCompleted: console.log("text2 complete")
//        }
//    }

//    Rectangle {
//        id: rect2
//        width: 300
//        height: 200
//        y: 300
//        Text {
//            id: txt2
//            focus: true
//            text: qsTr("text2: " +txt2.focus + " activeFocus2: "+ txt2.activeFocus)
//            Component.onCompleted: console.log("text2 complete")
//        }
//    }

//// 3、FocusScope 控件的子控件都能获取到焦点，focus 为true； FocusScope控件设置了 focus 则子控件的 focus 设置可以让 activeFocus 也为 true
//// 简单逻辑用 focus 设置为true 没问题，但是复杂控件，需要用 activeFocus
    FocusScope {
        id: rect
        width: 300
        height: 200
        focus: true             // 父控件 设置焦点，子控件
        Text {
            id: txt1
            focus: true
            text: qsTr("text1: " +txt1.focus + " activeFocus1: "+ txt1.activeFocus)
            Component.onCompleted: console.log("text2 complete")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                txt1.forceActiveFocus()     // activeFocus 为 readonly ，可以通过该接口修改焦点
            }
        }
    }

    FocusScope {
        id: rect2
        width: 300
        height: 200
        y: 300
        Text {
            id: txt2
            focus: true
            text: qsTr("text2: " +txt2.focus + " activeFocus2: "+ txt2.activeFocus)
            Component.onCompleted: console.log("text2 complete")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                txt2.forceActiveFocus()
            }
        }
    }

}
