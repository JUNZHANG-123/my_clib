import QtQuick 2.12
import QtQuick.Controls 2.12
import Skin 1.0

Item {
    id: root
    anchors.fill: parent
    property alias popupVisible: popup.visible
    property alias contentItem: popup.contentItem
    property color barColor: "white"
    property alias backgroundItem: background
    property real backgroundWidth: 200
    property real backgroundHeight: 160
    property color borderColor:  barColor
    property real borderWidth: 0
    readonly property int triangleBottom: 0
    readonly property int triangleTop: 1
    property int trianglePos: triangleTop

    property real verticalOffset: 5
    //矩形旋转45度，一半被toolTip遮住(重合)，另一半三角形和ToolTip组成一个带箭头的ToolTip
    Rectangle {
        id: bar
        visible: popup.visible
        rotation: 45
        width: 16
        height: 16
        color: barColor
        //水平居中
        anchors.horizontalCenter: parent.horizontalCenter
        y: trianglePos === triangleTop ? parent.height+verticalOffset: -height-verticalOffset
    }
    Popup {
        id: popup
        width: backgroundWidth
        height: backgroundHeight
        background: Rectangle {
            id: background
            color: barColor
            radius: 8
            border.color:borderColor
            border.width: borderWidth
        }
    }
    function show() {
        popup.x = (root.width - popup.width) / 2
        popup.y = trianglePos === triangleTop ? root.height+bar.height/2+verticalOffset : -popup.height-bar.height/2-verticalOffset
        popupVisible = true
    }
    function hide() {
        popupVisible = false
    }
}
