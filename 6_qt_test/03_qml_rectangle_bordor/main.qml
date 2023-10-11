import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MyRectangle {
        x: 100
        y: 100
        width: 100
        height: 100
        myTopMargin: 20
        myButtomMargin: 20
    }
}
