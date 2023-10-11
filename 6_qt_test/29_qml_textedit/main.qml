import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    Rectangle {
        width: 136
        height: 120
        color: "linen"
        MyTextEdit {
            id: input
            x: 8; y: 8
            width: 120; height: 104
            focus: true
            text: "Text Edit"
        }
    }




}
