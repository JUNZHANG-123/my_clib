import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    Text {
//        id: txt
//        text: qsTr("text 123 123")

//        Component.onCompleted: {
//            console.log(contentWidth)           // contentWidth / contentHeight 可以获取文本宽高
//            console.log(contentHeight)
//        }
//    }


//// 2、text 省略示例
//    Rectangle {
//        width: 50
//        height: 50
//        anchors.centerIn: parent
//        border.color: "black"

//        Text {
//            id: txt
//            elide: Text.ElideRight                  // 尾部省略 ...   锚点配置后才生效
//            anchors.fill: parent
//            text: qsTr("12131313131313131")
//        }
//    }

// 3、属性介绍
//    Text {
//        id: txt
//        text: qsTr("text")
//        font.family: "Courier New"          // 修改字体
//        font.bold: true                     // 粗体
//        font.italic: true                   // 斜体
//        font.letterSpacing: 10              // 文本中字间距
//        font.pixelSize: 36                  // 修改字体大小 像素单位
//        font.underline: true                // 下划线


//        Component.onCompleted: {
//            console.log(lineCount)          // 字体行数
//            console.log(lineHeight)         // 行间距 real 型
//        }
//    }

// 4、标签
//    Column {
//          Text {
//              font.pointSize: 24                        // html 语法
//              text: "<b>Hello</b> <i>World!</i>"
//          }
//          Text {
//              font.pointSize: 24
//              textFormat: Text.RichText                 // 富文本
//              text: "<b>Hello</b> <i>World!</i>"
//          }
//          Text {
//              font.pointSize: 24
//              textFormat: Text.PlainText                // 纯文本
//              text: "<b>Hello</b> <i>World!</i>"
//          }
//      }


//// 5、自动换行
//    Rectangle {
//        id: rect
//        width: 100
//        height: 200
//        border.color: "black"

//        Text {
//            id: txt
//            text: qsTr("text text text text text text text")
//            wrapMode: Text.WordWrap     // 自动单词换行
//            anchors.fill: parent
//            elide: Text.ElideRight
//        }
//    }


//// 6、超链接
    Text {
        textFormat: Text.RichText
        text: "See the <a href=\"http://qt-project.org\">Qt Project website</a>."
        onLinkActivated: console.log(link + " link activated")                          // 点击超链接触发
        onLinkHovered: console.log("hoverd", link)                                      //
        onHoveredLinkChanged: console.log("hoverd link changed", hoveredLink)

        MouseArea {                     // 使用 MouseArea 后 onLinkActivated 等事件不会触发，需要在 onClicked 中做加载
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onClicked: {
                // 加载页面
            }
        }
    }



}
