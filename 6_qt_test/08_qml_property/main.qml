import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、基础类型
//    property int myWidth: width
//    property real myReal: 0.0
//    property string myString: "test"        // string 也可以赋值color，但是用 color 更规范，url类似
//    property color myColor: "black"
//    property url myUrl: "/main.qml"


//// 2、property 可以定义所有组件类型
//// 外部 rectangle 动态加载该文件中Component 中的组件
//    Component {
//        id: com
//        Button {
//            id: btn
//            width: 50
//            height: 50
//        }
//    }

//    MyRectangle {
//        id: myrect
//        // @disable-check M16
//        mycom: com

//    }


//// 3、如果不知道对方类型，或者说特殊/通用类型，所有类型都可以赋值
    property var myVar: ["aaa", 3, 4]

//// 4、list 可以放组件，或者数组
    property list<Rectangle> mylist


//// 5、属性前加readonly 则该属性不能被修改值
    readonly property int rectWidth: width

//// 6、外部一定要赋值，才能使用 required


//// 7、外部访问子控件，1种是通过属性赋值，比如 05 中例子4
    MyRectangle {
        Component.onCompleted: {
            newInnerRect.color = "blue"
        }
    }


}

