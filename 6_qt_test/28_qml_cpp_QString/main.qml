import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

//    ScrollView {
//        anchors.fill: parent

//        ListView {
//            width: parent.width
//            model: 20
//            delegate: ItemDelegate {
//                text: "Item " + (index + 1)
//                width: parent.width
//            }
//        }
//    }

//    Rectangle {
//        width: 240
//        height: 300
//        color: "white"

//        ListView {
//            id: list
//            anchors.fill: parent
//            anchors.margins: 20
//            clip: true
//            model: 100
//            delegate: numberDelegate
//            spacing: 5
//            highlight: highlightComponent
//            focus: true
//        }

//        Component {
//            id: highlightComponent
//            Rectangle {
//                width: ListView.view.width
//                color: "lightGreen"
//            }
//        }

//        Component {
//            id: numberDelegate
//            Item {
//                width: 40
//                height: 40
//                Text {
//                    anchors.centerIn: parent
//                    font.pixelSize: 10
//                    text: index
//                }

//                MouseArea {                                               // 点击区域
//                    anchors.fill: parent
//                    onClicked: {
//                        console.log("list current index:", list.currentIndex, "index:", index)                    // currentIndex 当前 delegate 高亮项, index 点击的项
//                        list.currentIndex = index
//                    }
//                }
//            }
//        }
//    }

    Rectangle {
        width: 200
        height: 80
        color: "linen"

        TextInput {
            id: input1
            x: 8; y: 8
            width: 96; height: 20
            focus: true
            text: "Text Input 1"
            KeyNavigation.tab: input2
        }

        TextInput {
            id: input2
            x: 8; y: 36
            width: 96; height: 20
            text: "Text Input 2"
            KeyNavigation.tab: input1
        }
    }





}
