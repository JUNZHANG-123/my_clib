import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    property alias img_src: _image.source
    radius: 6
    signal imageStatusChanged(var sta);

    Image {
        id: _image
        asynchronous:true
        cache: false
        //smooth: true
        visible: false
        anchors.fill: parent
        fillMode:  Image.PreserveAspectCrop
        source: img_src
        sourceSize: Qt.size(parent.width, parent.height)
        antialiasing: true

        onStatusChanged: {
            imageStatusChanged(status)
        }

    }

    Rectangle {
        id: _mask
        color: "black"
        anchors.fill: parent
        radius: parent.radius
        visible: false
        antialiasing: true
        //smooth: true
    }
    OpacityMask {
        id: mask_image
        anchors.fill: _image
        source: _image
        maskSource: _mask
        visible: true
        antialiasing: true
    }
}
