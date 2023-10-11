import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、弹窗基本使用，使用 contentItem 自定义 popup
    Button {
        text: "Open"
        onClicked: popup.open()     // popup 打开函数，同样有 close 函数
    }

    Popup {
        id: popup
        x: 100
        y: 100
        width: 300
        height: 300
        modal: false               // 魔态对话框，弹窗外部颜色改变，如果弹窗未关闭则弹窗外面界面不能点击
        dim: true                 // 非魔态的背景色是否需要设置

        focus: true
        //visible: true           // 默认不显示，设置为true 则会直接显示
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent        // 关闭策略为 点击外部，或者点击esc 会退出，如果不想退出，则设置为 NoAutoClose

        contentItem: Rectangle {        // 和background 一样可以设置内容
            anchors.fill: parent
            border.color: "black"
            color: "grey"
            opacity: 0.9
            Text {
                id: txt
                anchors.fill: parent
                text: qsTr("message box area!!!")
                font.pixelSize: 26
                wrapMode: Text.WordWrap
            }

            Button {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 30
                text: qsTr("cancle")
            }

            Button {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.left: parent.left
                anchors.leftMargin: 30
                text: qsTr("ok")
            }
        }
    }


//// 2、popup 例外
//    Rectangle {
//        width: 200
//        height: 100
//        color: "black"
//        //visible: false                // 父控件隐藏则所有子控件也隐藏，子控件设置了也没用， 但是popup 是例外
//        Rectangle {
//            width: 50
//            height: 50
//            color: "red"
//            visible: true
//        }
//    }

//    Rectangle {
//        width: 200
//        height: 100
//        color: "black"
//        visible: false                // 父控件隐藏则所有子控件也隐藏，子控件设置了也没用， 但是popup 是例外

//        Popup {                       // popup 的 z 顺序覆盖于其他子控件之上，只会在popup 之间有顺序
//            width: 50
//            height: 50
//            visible: true
//        }
//    }






}
