import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、简单使用
//    Column {                // 列对齐
//        id: col
//        spacing: 30         // 间隔
//        Button {
//            width: 100
//            height: 50
//        }
//        Button {
//            width: 100
//            height: 50
//        }
//        Button {
//            width: 100
//            height: 50
//        }
//    }

//// 2、 添加repeater 使用
//    Column {
//        id: col
//        spacing: 30
//        leftPadding: 50       // Padding 设置内边距  （Margin 外边距）
//        Repeater {
//            model: 3
//            Button {
//                width: 100
//                height: 50
//                text: "btn" + index
//            }
//        }

//        move: Transition {
//                 NumberAnimation { properties: "x,y"; duration: 1000 }
//        }
//        populate: Transition {
//                 NumberAnimation { properties: "x,y"; from:200; duration: 1000; easing.type: Easing.OutBounce }
//        }
//    }

//// 3、点击按钮添加按键，使用布局自动向下排列，布局中使用 move/ add/populate 添加动画
//    Column {
//        id: col
//        spacing: 30
//        Repeater {
//            id: rep
//            model: ListModel {

//            }
//            Button {
//                width: 100
//                height: 50
//                text: name      // ListModel 参数name
//            }
//        }

//        move: Transition {
//                 NumberAnimation { properties: "x,y"; duration: 1000 }
//        }
//        add: Transition {
//                 NumberAnimation { properties: "x,y"; duration: 1000 }
//        }
//        populate: Transition {
//                 NumberAnimation { properties: "x,y"; from:200; duration: 1000; easing.type: Easing.OutBounce }
//        }
//    }

//    Button {
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
//        anchors.leftMargin: 20
//        onClicked: {
//            rep.model.insert(0, {"name": rep.model.count})
//        }
//    }

//// 4、行布局
//    Row {
//        id: col
//        spacing: 30
//        leftPadding: 50
//        layoutDirection: Qt.RightToLeft     // 改变绘制方向
//        Repeater {
//            model: 3
//            Button {
//                width: 100
//                height: 50
//                text: "btn" + index
//            }
//        }

//        move: Transition {
//                 NumberAnimation { properties: "x,y"; duration: 1000 }
//        }
//        populate: Transition {
//                 NumberAnimation { properties: "x,y"; from:200; duration: 1000; easing.type: Easing.OutBounce }
//        }
//    }

//// 5、flow 流式布局
//    Rectangle {
//        width: 400
//        height: 300
//        border.color: "black"

//        Flow {                  // flow 会根据父控件大小自动换行，流式布局
//          anchors.fill: parent
//          anchors.margins: 4
//          spacing: 10
//          flow: Flow.TopToBottom        // Flow.TopToBottom 从上往下， Flow.LeftToRight (default) 从左往右

//          Text { text: "Text"; font.pixelSize: 40 }
//          Text { text: "items"; font.pixelSize: 40 }
//          Text { text: "flowing"; font.pixelSize: 40 }
//          Text { text: "inside"; font.pixelSize: 40 }
//          Text { text: "a"; font.pixelSize: 40 }
//          Text { text: "Flow"; font.pixelSize: 40 }
//          Text { text: "item"; font.pixelSize: 40 }
//      }
//    }


    Grid {
        columns: 3      // 可以手动控制有几行几列， flow 不行
        rows: 3
        spacing: 2
        Rectangle { color: "red"; width: 50; height: 50 }
        Rectangle { color: "green"; width: 20; height: 50 }
        Rectangle { color: "blue"; width: 50; height: 20 }
        Rectangle { color: "cyan"; width: 50; height: 50 }
        Rectangle { color: "magenta"; width: 10; height: 10 }
    }
}
