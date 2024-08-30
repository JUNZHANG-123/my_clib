import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0
import "./qmls"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Item {
        width: 200
        height: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        CircularImage {
            id: cover_img
            anchors.fill: parent
            radius: 100
            img_src: "qrc:/images/people.png"
        }
    }

}
