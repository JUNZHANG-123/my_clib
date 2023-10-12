import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id:topbtn
        width: 64
        height: 64
        visible: false
        anchors.right: parent.right
        anchors.rightMargin: 24
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 24
        z:21
        color: mouseid.pressed ? "#CC12CFA7":"#FF12CFA7"
        radius: 16

//        Image{
//            id : topbtnicon
//            anchors.centerIn: parent
//            source: "qrc:/images/up_arrow.png"
//        }

        MouseArea {
            id:mouseid
            anchors.fill: parent
            anchors.margins: -20
            onClicked: {
                console.log("clicked: to top")
                toTop();
                flicktimer.stop();
            }
        }
    }

    function toTop(){
        flickable.contentY = 0;
    }

    Flickable {
        id: flickable
        anchors.top: parent.top         // 固定顶部
        anchors.left: parent.left       // 固定左边
        anchors.leftMargin: 120
        anchors.right: parent.right     // 固定右边
        anchors.rightMargin: 120
        anchors.bottom: parent.bottom
        contentHeight: image.height + 30
        ScrollBar.vertical: ScrollBar {visible: false } //创建一个竖向的滚动条
        clip : true

//        onContentYChanged: {
//            console.log("y:", contentY)
//        }
//        onContentXChanged: {
//            console.log("x:", contentX)
//        }


        Timer{
            id:flicktimer
            interval: 1500;
            repeat: false;
            running: false
            onTriggered: {                       // 定时器触发函数
                topbtn.visible = false;
            }
        }

        onFlickStarted:
        {
            if(contentY > 10) {                  // && preContentY >contentY
                topbtn.visible = true;
                flicktimer.stop();
                console.log("onFlickStarted: checked")
            }
        }

        onMovementEnded: {
            flicktimer.restart();                // 移动结束后开始计时
            console.log("onMovementEnded")
        }

        Image { id: image; source: "qrc:/R-C.png" }
    }


}
