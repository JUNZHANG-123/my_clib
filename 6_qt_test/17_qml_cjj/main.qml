import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import MyObj 1.0

Window {
    id: window
    objectName: "win"
    visible: true
    width: SCREEN_WIDTH         // 属性用冒号方式赋值是动态绑定方式，后面值改变会通知前面值改变；用等号方式赋值不会
    height: 480
    title: qsTr("Hello World")

    MyRectangle {

        Component.onCompleted: {
            attr.testValue = 200          // 使用别名，调用外部qml中子控件的属性
            console.log(attr.testValue)
        }
    }

    MyObect {           // 调用c++ 中的类
        id: myobj
        iValue: 10
        sString: "zhangsan"

        Component.onCompleted: {
            console.log(iValue, sString)
        }
    }

//// 1、qml 中设置信号，在qml中绑定，或c++中绑定

    // qml 中调用 c++ 中函数
//    Button {
//        onClicked: {
//            myobj.iValue = 10
//            myobj.func()
//            console.log(myobj.iValue, myobj.sString)
//        }
//    }

    // qml 中发送信号，c++ 端接收
//    signal qmlSig(int i, string s)
//    Button {
//        objectName: "btn"
//        onClicked: {
//            qmlSig(10, "zhangsan")  // 发出信号
//        }
//    }

    // 1、用 Connections 绑定信号和槽
//    Connections {       // 绑定信号和槽函数
//        target: window
//        onQmlSig: {
//            myobj.cppSlot(i, s)
//        }
//    }

    // 2、用信号的 connect 方法绑定信号和槽
//    Component.onCompleted: {
//        qmlSig.connect(myobj.cppSlot)
//    }

    // 3、c++ 端实现绑定信号和槽 ，查看 main.cpp


//// 2、c++ 中设置信号 cppSig，在qml 中接收绑定
    // 1、设置接收槽函数
    function myqmlSolt(i, s) {
        console.log("qml", i, s)
    }

    Button {
        objectName: "btn"
        onClicked: {
            //myobj.cppSig(10, "lisi")  // 发出c++信号
            myobj.func()                // 或者调用c++ 中函数发送
        }
    }

    Connections {       // 绑定信号和槽函数
        target: myobj
        onCppSig: {
            myqmlSolt(i, s)
        }
    }

}
