import QtQuick 2.12
import QtQuick.Controls 2.5
import "./qmls"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

// 官方demo
//    SwipeView {
//        id: swipeView
//        anchors.fill: parent
//        currentIndex: tabBar.currentIndex

//        Page1Form {
//        }

//        Page2Form {
//        }
//    }

//    footer: TabBar {
//        id: tabBar
//        currentIndex: swipeView.currentIndex

//        TabButton {
//            text: qsTr("Page 1")
//        }
//        TabButton {
//            text: qsTr("Page 2")
//        }
//    }

    MySwipview {
        anchors.fill: parent
    }
}
