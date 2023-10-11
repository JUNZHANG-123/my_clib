import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、使用 Component.onCompleted: 加log 来调试qml
//    Component.onCompleted: {                // 控件创建完成槽函数
//        console.log("onCompleted")
//    }

//    Component.onDestruction: {              // 控件销毁
//        console.log("onDestruction")
//    }


//// 2、使用loader 异步加载控件
//    Component {
//        id: com
//        Rectangle {
//            id: rect
//            width: 200
//            height: 100
//            color: "black"

//            Component.onCompleted: {                // 控件创建完成槽函数
//                console.log("onCompleted")
//            }

//            Component.onDestruction: {              // 控件销毁
//                console.log("onDestruction")
//            }
//        }
//    }

//    Loader {
//        id: loader
////        source: "/MyRectangle.qml"                        // source 只能加载qml 文件
//        sourceComponent: com                                // sourceComponent 加载component
//        asynchronous: true                                  // 是否异步加载，打开则loader 未完成时状态为 loading/2
//        onStatusChanged: {
//            console.log("onStatesChanged:", status)
//        }
//    }

//    Button {
//        width: 100
//        height: 100
//        x: 300
//        onClicked: {
////            loader.sourceComponent = null                 // 点击销毁loader 加载的控件

//            loader.item.width = 50                          // 加载完成后修改属性，使用 loader.item.
//            loader.item.height = 50
//            loader.item.color = "red"

//        }
//    }


//// 3、使用component 加载图片
//    Component {
//        id: com
////        Image {                     // 加载静态图像
////            id: img
////            source: "/th.jpg"
////            width: 50               // 调整大小，缩放
////            height: 50
////        }
//        AnimatedImage {               // 加载动态图像
//            id: img
//            source: "/th2.gif"

//        }
//    }

//    Loader {
//        id: loader
//        sourceComponent: com
//        asynchronous: true                                  // 是否异步加载，打开则loader 未完成时状态为 loading/2
//        onStatusChanged: {
//            console.log("onStatesChanged:", status)
//        }
//    }

//    Button {
//        width: 100
//        height: 100
//        x: 300
//        onClicked: {
//            loader.item.paused = !loader.item.paused        // 动图可以设置暂停
//        }
//    }

// 4、使用loader 异步控制 MyRectangle.qml 并
    Loader {
        id: loader
        source: "/MyRectangle.qml"                        // source 只能加载qml 文件
        asynchronous: true                                  // 是否异步加载，打开则loader 未完成时状态为 loading/2
        onStatusChanged: {
            console.log("onStatesChanged:", status)
        }
    }

    Button {
        width: 100
        height: 100
        x: 300
        onClicked: {
//            loader.sourceComponent = null                 // 点击销毁loader 加载的控件

            loader.item.myTopMargin = 10                          // 加载完成后修改属性，使用 loader.item.  只能设置一级属性
            loader.item.myButtomMargin = 10
            loader.item.color = "red"
        }
    }

}
