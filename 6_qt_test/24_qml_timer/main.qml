import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property int time: 0

    Timer {
        id: timer
        interval: 1000      // 时间间隔
        running: true     // 默认开启
        repeat: true        // 是否重复触发
        triggeredOnStart: true  // 立刻触发，不需要等1秒
        onTriggered: {      // 触发回调函数
            time += 1
        }
    }

    Text {
        id: txt
        text: time
        font.pixelSize: 68
        anchors.centerIn: parent
    }

    Button {
        id: btn
        text: "start"
        width: 100
        height: 200
        onClicked: {
            //timer.start()     // 开启
            timer.restart()     // 重新开启
            //timer.stop()      // 停止
        }
    }
}
