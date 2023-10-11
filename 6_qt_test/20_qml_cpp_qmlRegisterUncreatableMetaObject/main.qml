import QtQuick 2.10
import QtQuick.Window 2.10
import MyObj 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    MyObject {        // 使用 qmlRegisterUncreatableMetaObject 注册的类不能创建实例
//    }

    Component.onCompleted: {
        console.log(MyObject.Key2, " value: ", MyObject.iValue, MyObject.func())       // 使用C++ 枚举
    }
}
