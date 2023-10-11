import QtQuick 2.10
import QtQuick.Window 2.10

import "setting"            // 导入 setting 目录下文件，其中 qmldir 声明

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        width: 480
        height: 200
        Text {
            id: txt
            text: qsTr("text")
            font.pixelSize: Setting.myPixelSize
            color: Setting.textColor
        }
    }
}
