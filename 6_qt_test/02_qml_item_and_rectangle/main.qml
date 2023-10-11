import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、z 轴示例
//    Rectangle {
//        x: 100
//        y: 100
//        z: 0
//        width: 100
//        height: 50
//        color: "black"
//    }
//    Rectangle {
//        x: 120
//        y: 120
//        z: 1
//        width: 100
//        height: 50
//        color: "blue"
//    }



//// 2、焦点示例
//    Rectangle {
//        x: 100
//        y: 100
//        focus: true                             // 控件需要接收键盘或其他信息时，需要将当前控件设置为焦点
//        width: 100
//        height: 50
//        color: "black"
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                console.log("onclick")
//            }
//        }
//        Keys.onReturnPressed: {                 // 回车键
//            console.log("onReturnPressed")
//        }
//    }


//// 3、绝对坐标设置示例
//    Rectangle {
//        id: rect1
//        width: 100
//        height: 50
//        color: "black"
//    }
//    Rectangle {
//        x: rect1.width +20                        // 绝对坐标
//        id: rect2
//        width: 100
//        height: 50
//        color: "black"
//    }


//// 4、anchors/锚点 示例1  填充满父控件
//    Rectangle {
//        id: rect1
//        anchors.fill: parent                        // 整个填充满父控件，宽高将会无效， item 里面会有更多介绍
//        color: "red"
//    }


//// 5、anchors/锚点 示例2  右对齐
//    Rectangle {
//        id: rect1
//        width: 100
//        height: 50
//        color: "black"
//    }
//    Rectangle {
//        id: rect2
//        width: 100
//        height: 50
//        color: "black"
//        anchors.left: rect1.right                   // 右对齐 rect1的左边
//        anchors.leftMargin: 20                      // 间隔 20
//    }


//// 6、rotation 旋转
//    Rectangle {
//        width: 100
//        height: 50
//        color: "black"
//        rotation: 50
//    }


//// 7、scale 缩放
//    Rectangle {
//        width: 100
//        height: 50
//        color: "black"
//        scale: 0.5
//    }


//// 8、Rectangle 基本参数示例
//    Rectangle {
//        x: 100
//        y: 200
//        width: 100
//        height: 100
//        color: "black"
//        antialiasing: true          // 抗锯齿，曲线中才有差别
//        border.color: "red"         // 边框，整个控件宽度没有改变，只是往内部缩
//        border.width: 30
//        radius: 15                  // 圆角弧度
//    }


//// 9、Rectangle gradient 颜色渐变示例
//    Rectangle {
//        y: 0; width: 80; height: 80
//        color: "lightsteelblue"
//    }
//    Rectangle {
//        y: 100; width: 80; height: 80                    // 同一行中间用封号
//        gradient: Gradient {
//            GradientStop { position: 0.0; color: "lightsteelblue" }     // 颜色变化
//            GradientStop { position: 1.0; color: "blue" }
//        }
//    }














}
