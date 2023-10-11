import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        width: 200
        height: 300
        model: MyListModel
        delegate: Text {
            id: txt
            text: name + " " + value
        }

    }
}
