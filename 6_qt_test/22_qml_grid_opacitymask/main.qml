import QtQuick 2.10
import QtQuick.Window 2.10
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    Grid {
        id: grid
        width: 15
        height: 200
        columns: 3
        anchors.centerIn: parent

        Repeater {
            model: grid.width / 5 * 200 / 5  //grid.width / 5 * grid.height / 5         // 如果是减小 grid.height 那么改变后，Repeater 会重新绘制，消耗资源
            Rectangle {
                width: 5
                height: 5
                color: index % 2 ? "black" : "white"
            }
        }
    }

    Rectangle {
        id: maskRect
        width: grid.width
        height: grid.height
        radius: 10
        border.color: "black"
    }

    Rectangle {
        width: grid.width + 4
        height: grid.height +4      // 往外扩大 4 pixel
        border.color: "red"
        border.width: 3
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter       // 通过这2行可以固定一端位置，如果减掉高度，底部也会对齐
        anchors.bottom: parent.bottom

        OpacityMask {               // 子控件会覆盖父控件
            source: grid            // 合并源
            maskSource: maskRect    // 遮盖源
            anchors.fill: parent
            anchors.margins: 2      // 往内收缩2 pixel
        }
    }

    Button {
        width: 50
        height: 50
        x : 300
        onClicked: {
            grid.height -= 10       // 点击高度减10
        }
    }

}
