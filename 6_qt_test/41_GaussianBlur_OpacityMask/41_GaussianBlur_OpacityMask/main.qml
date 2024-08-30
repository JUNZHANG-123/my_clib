import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 1000
    height: 640
    title: qsTr("Hello World")

    Rectangle {
        id: rect1
        width: parent.width/3
        height: parent.height
        anchors.left: parent.left

        Image {
            asynchronous:true
            cache: false
            anchors.fill: parent
            source: "qrc:/images/people.png"
            sourceSize: Qt.size(parent.width, parent.height)
            antialiasing: true
        }
    }

    Rectangle {
        id: rect2
        width: parent.width/3
        height: parent.height
        anchors.left: rect1.right

        Image {
            asynchronous:true
            cache: false
            anchors.fill: parent
            source: "qrc:/images/butterfly.png"
            sourceSize: Qt.size(parent.width, parent.height)
            antialiasing: true
        }
    }

    Rectangle {
        id: rect3
        width: parent.width/3
        height: parent.height
        anchors.left: rect2.right

        Item {
            id: blurItem
            visible: false
            anchors.fill: parent

            Image {
                id: backgroundImage
                asynchronous:true
                cache: false
                visible: false
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: "qrc:/images/people.png"
                sourceSize: Qt.size(parent.width, parent.height)
                antialiasing: true
            }

            GaussianBlur {
                anchors.fill: parent
                source: backgroundImage
                radius: 10
            }
        }

        Image {
            id: maskImage
            anchors.fill: parent
            source: "qrc:/images/butterfly.png"
        }

        OpacityMask {
            anchors.fill: blurItem
            source: blurItem
            maskSource: maskImage
            visible: true
        }
    }
}
