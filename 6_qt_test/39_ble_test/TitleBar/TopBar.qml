import QtQuick 2.0
import QtQuick.Window 2.12
import "qrc:/CusWidgets" as CusWidgets
import Skin 1.0
Item {
    id: root
    property int windowVisibility: -1
    signal maxWinClicked()
    signal minWinClicked()
    Row {
        anchors.fill: parent
        anchors.rightMargin: 0
        layoutDirection: Qt.RightToLeft
        // 关闭窗口
        CusWidgets.ImageButton {
            source: "qrc:/images/close.png"
            imageColor: "#ccc"
            imageHoverColor: "white"
            hoverColor: "red"
            imagePadding: 8
            width: 50
            height: 30
            onClicked: {
                Qt.quit()
            }
        }
        // 最大化窗口
        CusWidgets.ImageButton {
            source:  {
                if (root.windowVisibility === Window.FullScreen)
                    return "qrc:/images/winmax.png"
                else
                    return "qrc:/images/winreturn.png"
            }
            imageColor: "#ccc"
            imageHoverColor: "white"
            hoverColor: Qt.darker(Skin.background, 1.2)
            imagePadding: 8
            width: 50
            height: 30
            onClicked: {
                maxWinClicked()
            }
        }
        // 最小化窗口
        CusWidgets.ImageButton {
            source: "qrc:/images/winmin.png"
            imageColor: "#ccc"
            imageHoverColor: "white"
            hoverColor: Qt.darker(Skin.background, 1.2)
            imagePadding: 8
            width: 50
            height: 30
            onClicked: {
                minWinClicked()
            }
        }
        // 换皮肤按钮
        CusWidgets.ImageButton {
            source: "qrc:/images/skin.png"
            imageColor: "#ccc"
            imageHoverColor: "white"
            hoverColor: Qt.darker(Skin.background, 1.2)
            imagePadding: 8
            width: 50
            height: 30
            onClicked: {
                if (skinpopWin.popupVisible === true) {
                    skinpopWin.hide()
                } else {
                    skinpopWin.show()
                }
            }

            SkinPopWindow {
                id: skinpopWin
            }
        }
    }
}
