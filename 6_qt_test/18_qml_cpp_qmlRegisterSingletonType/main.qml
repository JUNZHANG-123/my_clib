import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import MyObj 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    function myqmlSolt(i, s) {      // c++ 端要发送信号给qml ，信号中参数都是 QVariant
        console.log("qml", i, s)
    }

    Button {
        objectName: "btn"
        onClicked: {
            MyObject.func()
            console.log("key2:", MyObject.Key2)
        }
    }

//    Connections {       // 绑定信号和槽函数
//        target: MyObject
//        onCppSig: {
//            myqmlSolt(i, s)
//        }
//    }
}
