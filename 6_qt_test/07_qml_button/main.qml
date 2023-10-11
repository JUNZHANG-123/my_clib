import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、btn checked 示例
//    Button {
//        id: btn1
//        width: 100
//        height: 50
//        checkable: true                 // 可以修改 checked 的状态，如果是checked ，则按键高亮
//        checked: true                   // 默认被选中
//        onCheckableChanged: {
//            console.log("onCheckableChanged:", checkable, "checked=", checked)
//        }
//        onClicked: {
//            console.log("click:", btn1.checked)
//        }
//    }

// 2、只有一个可以选中
//    Button {
//        id: btn1
//        width: 100
//        height: 50
//        checkable: true                 // 可以修改 checked 的状态，如果是checked ，则按键高亮
//        autoExclusive: true             // 开启后所有 button 只有一个会高亮
//    }

//    Button {
//        id: btn2
//        width: 100
//        height: 50
//        y: 100
//        checkable: true                 // 可以修改 checked 的状态，如果是checked ，则按键高亮
//        autoExclusive: true
//    }

//    Button {
//        id: btn3
//        width: 100
//        height: 50
//        y: 200
//        checkable: true                 // 可以修改 checked 的状态，如果是checked ，则按键高亮
//        autoExclusive: true
//    }


//// 3、autoRepeat
//    Button {
//        id: btn1
//        width: 100
//        height: 50
//        autoRepeat: true                 // 重复响应按键

//        onPressed: {
//            console.log("pressed")
//        }
//        onReleased: {
//            console.log("release")
//        }
//        onClicked: {
//            console.log("clicked")
//        }
//    }

//// 4、indicator 加载图片
//    Button {
//        id: btn1
//        width: 100
//        height: 50
//        indicator: Image {
//            id: ind
//            source: "/th.jpg"
//            width: 20
//            height: 20
//            anchors.centerIn: parent
//        }
//    }

//// 5、text
//    Button {
//        id: btn1
//        width: 100
//        height: 50
//        text: "btn1"
//    }


// 6、使用background 来调整背景及按键其他属性
//    Button {
//        id: btn1
//        width: 100
//        height: 50
//        background: Rectangle {
//            anchors.fill: parent
////            color: btn1.pressed ? "red" : "green"       // 可使用状态机，或者直接复制，2中写法
//            color : {
//                if (btn1.pressed)
//                    return "red"
//                else
//                    return "green"
//            }

//            border.width: 10                              // 边框
//            border.color: btn1.pressed ? "yellow" : "blue"
//        }
//    }


// 7、DelayButton
//    DelayButton {       // 点击进度条加载，变高亮，中间松开恢复
//        width: 150
//        height: 50
//        delay: 1000
//        onProgressChanged: {

//        }
//    }


// 8、自动排他，单选按键
//    Column {
//        RadioButton {
//            checked: true
//            text: qsTr("First")
//        }
//        RadioButton {
//            text: qsTr("Second")
//        }
//        RadioButton {
//            text: qsTr("Third")
//        }
//    }


// 9、开关按键
//    Column {
//        Switch {
//            text: qsTr("Wi-Fi")
//            LayoutMirroring.enabled: true                   // 镜像，  镜像后onPositionChanged/onVisualPositionChanged 才有差别
//            onPositionChanged: {                            // 实际位置，拖动按钮过程中，位置改变
//                console.log("onPositionChanged", position)
//            }

//            onVisualPositionChanged: {                      // 镜像后，视觉位置
//                console.log("onVisualPositionChanged", visualPosition)
//            }
//        }
//        Switch {
//            text: qsTr("Bluetooth")
//        }
//    }


// 10、定义button 集合属性
//    ButtonGroup {           // 使用buttonGroup 来实现switch 按键排他
//        id: btnGroup
//        exclusive: true
//        buttons: col.children   // col 的子buttons 控件将会继承该 Group 属性
//    }

//    Column {
//        id: col
//        Switch {
//            text: qsTr("Wi-Fi")
//        }
//        Switch {
//            text: qsTr("Bluetooth")
//        }
//    }


// 11、tab 按钮
//    TabBar {
//        TabButton {
//            text: qsTr("Home")
//        }
//        TabButton {
//            text: qsTr("Discover")
//        }
//        TabButton {
//            text: qsTr("Activity")
//        }
//    }

// 12、自定义button 实现 1 background 背景重绘
//    Button {
//        id: btn
//        width: 150
//        height: 100
//        background: Rectangle {
//            anchors.fill: parent
//            color: btn.checked | btn.down ? "black" : "blue"        // 附加属性中不能直接使用父类属性，一定要指定id
//        }
//    }

// 13、自定义button 实现 2 contentItem 内容重绘
    Button {
        id: btn
        width: 200
        height: 100
        padding: 0
        text: "Button"
//        contentItem: Label {
//            text: btn.text
//            font: btn.font
//            verticalAlignment: Text.AlignVCenter
//        }

//        contentItem: Text {
//            text: btn.text
//            font.pixelSize: 18      // 字体大小
//            font.bold: true         // 粗体
//            font.italic: true       // 斜体
//        }

        contentItem: Rectangle {
            color: "transparent"            // 设置为透明
            Text {
                id: text
                text: btn.text
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.left: parent.left                                   // x 轴对齐
                anchors.verticalCenter: parent.verticalCenter               // y轴对齐
                anchors.leftMargin: (parent.width-img.width-text.width)/2   // 页边距设置，设置完居中
            }

            Image {
                id: img
                source: "/th.jpg"
                width: 50
                height: 50
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: -1                         // 页边距调整：右边页边空白调整
            }
        }
    }
}




