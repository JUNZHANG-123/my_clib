import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、 CheckBox 示例
//    Column {
//         CheckBox {
//             checked: true
//             tristate: true             // 3态 √ - 空
//             text: qsTr("First")
//         }
//         CheckBox {
//             text: qsTr("Second")
//         }
//         CheckBox {
//             checked: true
//             text: qsTr("Third")
//         }
//     }


// 2、使用 ButtonGroup + Column 实现 checkBox 排他
//    ButtonGroup {
//        id: childGroup
//        exclusive: true
//        buttons: col.children
//    }

//    Column {
//        id: col
//         CheckBox {
//             checked: true
//             tristate: true             // 3态 √ - 空
//             text: qsTr("First")
//         }
//         CheckBox {
//             text: qsTr("Second")
//         }
//         CheckBox {
//             checked: true
//             text: qsTr("Third")
//         }
//     }

// 3、Button 中 设置 ButtonGroup，实现排他
//    ButtonGroup {
//        id: childGroup
//        exclusive: true
//    }

//    Column {
//        id: col
//         CheckBox {
//             checked: true
//             tristate: true             // 3态 √ - 空
//             text: qsTr("First")
//             ButtonGroup.group: childGroup
//         }
//         CheckBox {
//             text: qsTr("Second")
//             ButtonGroup.group: childGroup
//         }
//         CheckBox {
//             checked: true
//             text: qsTr("Third")
//             ButtonGroup.group: childGroup
//         }
//     }

}
