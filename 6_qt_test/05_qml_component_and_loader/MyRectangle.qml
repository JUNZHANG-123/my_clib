import QtQuick 2.0

Rectangle {
    id: bordorRect
    width: 200
    height: 100
    color: "black"      // 边框颜色
    property int myTopMargin: 0
    property int myButtomMargin: 0

    Rectangle {
        id: innerRect
        anchors.fill: parent
        anchors.topMargin: myTopMargin              // 页边空白
        anchors.bottomMargin: myButtomMargin
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        color: "blue"
    }
}
