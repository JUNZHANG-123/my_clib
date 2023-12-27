import QtQuick 2.12
import QtQuick.Controls 2.5
import BleConnect.module 1.0
import Skin 1.0
import Config 1.0

Item {
    id: root
    anchors.fill: parent
    anchors.topMargin: 30

    property var bleMsg: ""

    signal sigBleConnected()

    Grid {
         id: leftBar
         columns: 1
         rows: 2
         spacing: 0
         width: 200

         anchors.left: parent.left
         anchors.top: parent.top
         anchors.bottom: parent.bottom

         Button {
             id: bleStopSearch
             width: parent.width
             height: 40
             text: qsTr("停止搜索")
             onClicked:{
                 console.log("bleStopSearch onClicked")
                 mainRoot.bleconnect.on_blue_stop_search_clicked();
             }
         }

         Button {
             id: bleRestartSearch
             width: parent.width
             height: 40
             text: qsTr("重新搜索")
             onClicked:{
                 console.log("bleRestartSearch onClicked")
                 listView.model.clear();
                 mainRoot.bleconnect.on_blue_search_clicked(true);
             }
         }
    }

    ListView {
        id: listView
        highlightMoveDuration: 100
        clip: true
        contentHeight: 160
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: leftBar.right
        anchors.right: parent.right
        highlightRangeMode: ListView.StrictlyEnforceRange
        boundsBehavior:Flickable.StopAtBounds

        delegate: Rectangle {
            id:warrap
            x: 5
            width: root.width - leftBar.width
            height: 80
            color: "white"
            border.color: "grey"

            Column {
                spacing: 5
                Text {
                    text: name
                    font.pixelSize: 20
                    font.weight: Font.DemiBold
                    color: "black"
                }
                Text {
                    text: mac
                    font.pixelSize: 20
                    font.weight: Font.Normal
                    color: "black"
                }
                Text {
                    text: rssi
                    font.pixelSize: 20
                    font.weight: Font.Normal
                    color: "black"
                }
            }

            Button {
                width: 50
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 50
                text: qsTr("连接")
                onClicked: {

                    mainRoot.bleconnect.on_blue_connect_clicked(mac);
                    console.log("onClicked", name)
                }
            }
        }
        model: ListModel {
        }

//        onFlickStarted: {
//             var sd = (Math.abs(verticalVelocity)+5000);
//             flick(0,verticalVelocity < 0 ? sd : -sd )
//        }

        ScrollBar.vertical: ScrollBar {
            id: verticalBar
            active: true
            hoverEnabled: true
            size: 10
            policy: ScrollBar.AlwaysOn
            contentItem: Rectangle {
                implicitWidth: 10
                implicitHeight: 10
                radius: width/2
                color: "gray"
            }
        }
    }

    Connections{
        target: mainRoot.bleconnect
        onAddItems:{
            listView.model.append({"name":name, "mac":mac, "rssi":rssi});
            //console.log("name", name, "mac", mac, "rssi", rssi)
        }

        onBleConnected:{
            console.log("onBleConnected")
            sigBleConnected()
        }
//        onFromBle:{

//        }
    }
}
