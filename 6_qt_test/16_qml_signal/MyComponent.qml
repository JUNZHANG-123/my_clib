import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    width: 400
    height: 300
    border.color: "black"

    property Component com1
    property Component com2

    Loader {
        id: loader1
        sourceComponent: com1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        Connections {
            target: loader1.item            // 不需要知道是谁发过来的信号，一定是这个控件的 item
            ignoreUnknownSignals: true      // 忽略未知信号，防止未定义信号报错
            onBtnSig: {
                console.log("left:", val)
            }
        }

        Connections {
            target: loader1.item            // 不需要知道是谁发过来的信号，一定是这个控件的 item
            ignoreUnknownSignals: true      // 忽略未知信号，防止未定义信号报错
            onLeftBtnPressed: {
                console.log("leftPress")
                loader2.item.focus = true
                loader2.item.forceActiveFocus()
                loader2.item.highlighted = true     // 按左键高亮
            }
        }

        Component.onCompleted: {
            loader1.item.focus = true
            loader1.item.forceActiveFocus()         // 默认 loader1 焦点
        }
    }

    Loader {
        id: loader2
        sourceComponent: com2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 200
        Connections {
            target: loader2.item            // 不需要知道是谁发过来的信号，一定是这个控件的 item
            ignoreUnknownSignals: true
            onBtnSig: {
                console.log("right:", val)
            }
        }
    }

}

