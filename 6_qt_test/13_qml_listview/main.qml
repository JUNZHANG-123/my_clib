import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、ListModel 使用示例
//    ListView {
//        width: 180; height: 200

//        model: ContactModel {}                  // ListModel
//        delegate: Text {                        // delegate 代理绘制
//            text: name + ": " + number          // 直接访问 ContactModel 中的元素
//        }
//    }

//// 2、
//    Rectangle {
//        width: 180; height: 200

//        Component {
//            id: contactDelegate
//            Item {
//                width: 180; height: 40
//                Column {
//                    Text { text: '<b>Name:</b> ' + name }
//                    Text { text: '<b>Number:</b> ' + number }
//                }
//            }
//        }

//        ListView {
//            anchors.fill: parent
//            model: ContactModel {}
//            delegate: contactDelegate
//            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }     //
//            focus: true
//        }
//    }


//    ListView {
//        width: 180; height: 200

//        Component {
//            id: contactsDelegate
//            Rectangle {
//                id: wrapper
//                width: 180
//                height: contactInfo.height
//                color: ListView.isCurrentItem ? "black" : "red"
//                Text {
//                    id: contactInfo
//                    text: name + ": " + number
//                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
//                }
//            }
//        }

//        model: ContactModel {}
//        delegate: contactsDelegate
//        focus: true
//    }

    MyListView {

    }

}
