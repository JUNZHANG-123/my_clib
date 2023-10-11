import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2


Window {
    id: win
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、示例1
    Button {
        width: 50
        height: 50
        onClicked: {
            testSig("aaa", 1)
        }
    }

    signal testSig(string s, int value)
    // 接收方法1
//    function func(ss, vv) {         // 定义函数
//        console.log(ss, vv)
//    }
//    Component.onCompleted: {
//        testSig.connect(func)       // 设置接收函数，通过信号.connect 方式
//    }

//    // 接收方法2
//    Connections {
//        target: win
//        onTestSig: {                    // 使用 on + 信号名（首字母大写）
//            console.log("2 ", s, value)
//        }
//    }

    // 接收方法3
//    function func(ss, vv) {         // 定义函数
//        console.log(ss, vv)
//    }
//    Connections {
//        target: win
//        onTestSig: func(s, value)
//    }



//// 示例2、使用 Component 将button 的click 信号传到外部控件中，在外部控件的 loader 中接收
//    Component {
//        id: com
//        Button {
//            signal btnSig(int val)
//            onClicked: {
//                console.log("clicked")
//                btnSig(1)
//            }
//        }
//    }
//    MyComponent {
//        com1: com
//        com2: com
//    }


//// 示例3、
    Component {
        id: com
        Button {
            signal leftBtnPressed
            Keys.onLeftPressed: {
                leftBtnPressed()
            }

        }
    }
    MyComponent {
        com1: com
        com2: com
    }




}
