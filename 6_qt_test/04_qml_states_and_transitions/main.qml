import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、states 控件属性状态机使用，鼠标点击释放后修改控件属性
    Rectangle {
        id: root
        width: 100; height: 100
        state: "normal"                  // 设置状态
        states: [                          // 定义了2个状态
            State {
                name: "red_color"
                PropertyChanges { target: root; color: "red"; width:200 }     // 不同状态，属性不同，PropertyChanges 修改属性
            },
            State {
                name: "blue_color"
                PropertyChanges { target: root; color: "blue" }
            },
            State {
                name: "normal"
                PropertyChanges { target: root; color: "black" }
            }
        ]
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            root.state = "red_color"            // 也可以直接修改属性，但是用 states 更规范
        }
        onReleased: {
            root.state = "blue_color"
        }
    }




}
