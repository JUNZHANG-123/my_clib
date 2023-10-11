import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、基本属性介绍
//    MouseArea {                     // MouseArea 不能直接显示，需要在内部包含 Rectangle
//        id: mouseArea
//        width: 200
//        height: 200
//        enabled: true               // 默认true, 当前事件使能，false 则所有事件都不触发
//        acceptedButtons: Qt.LeftButton | Qt.RightButton     // 左右键都可以触发
//        Rectangle {
//            anchors.fill: parent
//            color: "blue"
//        }

//        onPressed: {                // 注意：所有onXXX 函数也代表有对应属性
//            var ret = pressedButtons & Qt.LeftButton        // 判断是哪一个键按下
//            var ret2 = pressedButtons & Qt.RightButton
//            console.log("onPressed:", ret, ret2)
//        }

//        onReleased: {
//            console.log("onReleased")
//        }

//        onClicked: {                // 按下松开后为click
//            console.log("onClicked")
//        }

//        hoverEnabled: true
//        onContainsMouseChanged: {                                       // containsMouseChanged判断鼠标是否在该区域，hoverEnabled 为true 后，鼠标悬停就触发onContainsMouseChanged
//            console.log("onContainsMouseChanged", containsMouse)
//        }

//        onHoveredChanged: {
//            console.log("onHoveredChanged")
//        }

//        onContainsPressChanged: {
//            console.log("onContainsPressChanged", containsPress)        // 按下触发
//        }

//        onMouseXChanged: {                          // 鼠标x 改变
//            console.log("mouseX", mouseX)
//        }

//        onMouseYChanged: {
//            console.log("mouseY", mouseY)
//        }

//        cursorShape: Qt.CrossCursor                 // 悬停修改光标样式
//    }


//// 2、drag 拖拽属性介绍
//    Rectangle {
//        id: container
//        width: 600; height: 200

//        Rectangle {
//            id: rect
//            width: 50; height: 50
//            color: "red"
//            opacity: (600.0 - rect.x) / 600     // 透明度变化

//            MouseArea {
//                anchors.fill: parent
//                drag.target: rect               // 可以拖动 MouseArea 覆盖的target 区域
//                drag.axis: Drag.XAxis           // 拖动位置，设置往x 轴移动
//                drag.minimumX: 0                // 拖动范围：最小移动位置
//                drag.maximumX: container.width - rect.width // 最大移动位置
//            }
//        }
//    }

//// 3、drag 拖拽属性介绍
//    Rectangle {
//        width: 480
//        height: 320
//        Rectangle {
//            x: 30; y: 30
//            width: 300; height: 240
//            color: "lightsteelblue"

//            MouseArea {
//                anchors.fill: parent
//                drag.target: parent;
//                drag.axis: "XAxis"
//                drag.minimumX: 30
//                drag.maximumX: 150
//                drag.filterChildren: true           // 子控件是否继承父控件的 drag 事件

//                Rectangle {
//                    color: "yellow"
//                    x: 50; y : 50
//                    width: 100; height: 100
//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: console.log("Clicked")
//                    }
//                }
//            }
//        }
//    }


//// 4、长按触发 双击事件
//    MouseArea {                     // MouseArea 不能直接显示，需要在内部包含 Rectangle
//        id: mouseArea
//        width: 200
//        height: 200
//        enabled: true               // 默认true, 当前事件使能，false 则所有事件都不触发
//        acceptedButtons: Qt.LeftButton | Qt.RightButton     // 左右键都可以触发
//        Rectangle {
//            anchors.fill: parent
//            color: "blue"
//        }

//        pressAndHoldInterval: 3000
//        onPressAndHold: {           // 长按触发，默认800ms
//            console.log("onPressAndHold")
//        }

//        onDoubleClicked: {          // 双击事件
//            console.log("onPressAndHold")
//        }
//    }

//// 5、propagateComposedEvents 子控件是否要吞掉事件
//    Rectangle {
//        color: "yellow"
//        width: 100; height: 100

//        MouseArea {
//            anchors.fill: parent
//            onClicked: console.log("clicked yellow")
//        }

//        Rectangle {
//            color: "blue"
//            width: 50; height: 50

//            MouseArea {
//                anchors.fill: parent
//                propagateComposedEvents: true       //如果2个 区域重叠，默认事件只传递到最顶层控件，顶层会吞掉该事件。该属性打开后，则不会
//                onClicked: {
//                    console.log("clicked blue")
//                    mouse.accepted = false
//                }
//            }
//        }
//    }

}
