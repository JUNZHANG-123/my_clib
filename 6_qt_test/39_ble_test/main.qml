import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import Skin 1.0
import Config 1.0
import "qrc:/TitleBar" as TitleBar
import "qrc:/Ble" as BlePage
import BleConnect.module 1.0

Window {
    id: mainRoot
    visible: true
    title: qsTr("ble调试工具")
    width: 1225
    height: 765
    minimumWidth: 1225
    minimumHeight: 765
    color: "#00000000"  //设置窗口透明
    flags: Qt.FramelessWindowHint | Qt.Window

    property int margin: 15   // 阴影宽度
    property int pressX
    property int pressY
    property bool ignorePosition: false
    property var loaderSource: ""
    property var bleconnect: ble

    Rectangle {
        id: mainRect
        anchors.fill: parent
        anchors.margins: mainRoot.visibility === Window.FullScreen ? 0 : mainRoot.margin
        color: Skin.mainColor
        radius: 5
        visible: true

        MouseArea {
            id: mouse
            anchors.fill: parent

            onPressed: {
                pressX = mouseX  //mouseX是QML提供的
                pressY = mouseY
            }
            onPositionChanged: {
                if (!ignorePosition)
                {
                    mainRoot.x += mouseX - pressX
                    mainRoot.y += mouseY - pressY
                }
            }
            onDoubleClicked: {
                ignorePosition = true
                ignorePositionTimer.start()
                mainRoot.visibility = mainRoot.visibility === Window.FullScreen ? Window.AutomaticVisibility : Window.FullScreen
            }
        }

        Column {
            // topbar标题栏
            anchors.fill: parent
            TitleBar.TopBar {
                id: titleBar
                windowVisibility: mainRoot.visibility
                width: parent.width
                height: 50
                onMaxWinClicked: {
                    mainRoot.visibility = mainRoot.visibility === Window.FullScreen ? Window.AutomaticVisibility : Window.FullScreen
                    console.log("onMaxWinClicked", mainRoot.visibility, Window.FullScreen)
                }
                onMinWinClicked: {
                    mainRoot.visibility = Window.Minimized
                }
            }
        }

        Loader {
            id: pageSelectLoader
            anchors.fill: parent
            active: false
            source: loaderSource
            z:100
            onLoaded:
            {
                console.log("BleScanPage loaded");
            }
        }
    }

    Timer{
        id: ignorePositionTimer
        interval: 300;
        onTriggered: {
            console.log("ignorePositionTimer onTriggered")
            ignorePosition = false
        }
    }

    // 下面控件用于拖动伸缩窗口
    Item {//向左拖动
        id:leftSizeChange;
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: mainRoot.margin;
        visible: mainRoot.visibility === Window.FullScreen ? false : true

        MouseArea{
            anchors.fill:parent
            property point clickPos: "0,0"  //定义一个点
            cursorShape: Qt.SizeHorCursor
            onPressed: {
                clickPos = Qt.point(mouseX, mouseY)
            }

            onPositionChanged: {  //属性的改变
                var delta = Qt.point(mouseX-clickPos.x, mouseY-clickPos.y)
                if((mainRoot.width-delta.x)>mainRoot.minimumWidth) {
                   mainRoot.setX(mainRoot.x+delta.x)
                   mainRoot.setWidth(mainRoot.width-delta.x)
                }
                else
                    mainRoot.setWidth(mainRoot.minimumWidth)
            }
        }
    }

    Item {//向下拖动
        id:downSizeChange
        anchors.bottom: parent.bottom
        anchors.left: leftSizeChange.right
        anchors.right: rightSizeChange.left
        height: mainRoot.margin
        visible: mainRoot.visibility === Window.FullScreen ? false : true

        MouseArea{  //设置可以拖动没有标题的登录界面.  /*这个要放在上面，放在最下面的话，会把上面全部屏蔽掉的*/
            anchors.fill:parent
            property point clickPos: "0,0"  //定义一个点
            cursorShape:Qt.SizeVerCursor
            onPressed: {
                clickPos = Qt.point(mouseX, mouseY)
            }

            onPositionChanged: {  //属性的改变
                var delta = Qt.point(mouseX-clickPos.x, mouseY-clickPos.y)
                if((mainRoot.height+delta.y)>mainRoot.minimumHeight)
//                        mainRoot.setHeight(mainRoot.height+delta.y)
                    mainRoot.height += delta.y
                else
                    mainRoot.setHeight(mainRoot.minimumHeight)
            }
        }
    }

    Item {//向右拖动
        id:rightSizeChange;
        width: mainRoot.margin
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        visible: mainRoot.visibility === Window.FullScreen ? false : true

        MouseArea{
            anchors.fill:parent
            property point clickPos: "0,0"  //定义一个点
            cursorShape:Qt.SizeHorCursor
            onPressed: {
                clickPos = Qt.point(mouseX, mouseY)
            }

            onPositionChanged: {  //属性的改变
                var delta = Qt.point(mouseX-clickPos.x, mouseY-clickPos.y)
                if((mainRoot.width+delta.x)>mainRoot.minimumWidth) {
                   mainRoot.setWidth(mainRoot.width+delta.x)
                }
                else
                    mainRoot.setWidth(mainRoot.minimumWidth)
            }
        }
    }

    Item {//向上拖动
        id:upSizeChange
        anchors.bottom: mainRect.top
        anchors.left: leftSizeChange.right
        anchors.right: rightSizeChange.left
        height: mainRoot.margin
        visible: mainRoot.visibility === Window.FullScreen ? false : true

        MouseArea{
            anchors.fill:parent
            property point clickPos: "0,0"  //定义一个点
            cursorShape:Qt.SizeVerCursor
            onPressed: {
                clickPos = Qt.point(mouseX, mouseY)
            }

            onPositionChanged: {  //属性的改变
                var delta = Qt.point(mouseX-clickPos.x, mouseY-clickPos.y)
                if((mainRoot.height-delta.y)>mainRoot.minimumHeight) {
                    mainRoot.setY(mainRoot.y+delta.y)
                    mainRoot.setHeight(mainRoot.height-delta.y)
                }
                else
                    mainRoot.setHeight(mainRoot.minimumHeight)
            }
        }
    }


    BLE {
        id: ble
    }

    Connections{
        target: ble

        onBleConnected:{
            console.log("onBleConnected")
            pageSelectLoader.active = false;
            loaderSource = "qrc:/Ble/BleConnectedPage.qml"
            pageSelectLoader.active = true;
        }

        onBleDisconnected:{
            console.log("bleDisconnected")

            pageSelectLoader.active = false;
            loaderSource = "qrc:/Ble/BleScanPage.qml"
            pageSelectLoader.active = true;
//            pageSelectLoader.item.sigBleConnected.connect(function(){
//                console.log("pageSelectLoader sigBleConnected");
//                pageSelectLoader.active = false
//            });
        }
    }

    Component.onCompleted: {
        Skin.currentTheme = 5

        loaderSource = "qrc:/Ble/BleScanPage.qml"
        pageSelectLoader.active = true;
//        pageSelectLoader.item.sigBleConnected.connect(function(){
//            console.log("pageSelectLoader sigBleConnected");
//            pageSelectLoader.active = false
//        });
    }
}
