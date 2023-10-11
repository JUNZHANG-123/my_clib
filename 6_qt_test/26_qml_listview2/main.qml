import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import QtQml.Models 2.2
import QtQuick.XmlListModel 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    SwipeView {
//        id: view

//        currentIndex: 1
//        anchors.fill: parent

//        Item {
//            id: firstPage
//            Rectangle {
//                anchors.fill: parent
//                color: "lightsteelblue"
//            }
//        }
//        Item {
//            id: secondPage
//            Rectangle {
//                anchors.fill: parent
//                color: "gray"
//            }
//        }
//        Item {
//            id: thirdPage
//            Rectangle {
//                anchors.fill: parent
//                color: "black"
//            }
//        }
//    }

//    PageIndicator {
//        id: indicator

//        count: view.count
//        currentIndex: view.currentIndex

//        anchors.bottom: view.bottom
//        anchors.horizontalCenter: parent.horizontalCenter
//    }

//// 2、自定义 SwipeView 效果
//    Button {
//        id: btn
//        width: 200
//        height: 480
//        text: "btn"
//    }

//    ObjectModel {
//        id: myModel
//        Rectangle {
//            width: 440
//            height: 480
//            color: "lightsteelblue"
//        }
//        Rectangle {
//            width: 440
//            height: 480
//            color: "gray"
//        }
//        Rectangle {
//            width: 440
//            height: 480
//            color: "black"
//        }
//    }

//    ListView {
//        id: list
//        anchors.left: btn.right
//        anchors.right: parent.right
//        height: 480
//        model: myModel                      // 加载自定义 ObjectModel
//        orientation: ListView.Horizontal    // 行滑动
//        snapMode: ListView.SnapOneItem      // 每次滑动切换一个item
//        clip: true                          // 超出 ListView 部分不绘制
//    }

    XmlListModel {
        id: xmlModel
        source: "/MyXml.xml"                            // "http://www.mysite.com/feed.xml"
        query: "/rss/channel/item"                      // 子项是哪一项

        XmlRole { name: "title"; query: "title/string()" }          // listEmelents  每个项具体元素
        XmlRole { name: "pubDate"; query: "pubDate/string()" }
    }

    ListView {
          width: 180; height: 300
          model: xmlModel
          delegate: Text { text: title + ": " + pubDate }
      }
}
