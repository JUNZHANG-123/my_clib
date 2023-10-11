import QtQuick 2.0
import QtQuick.Controls 2.2

//ListView {
//    id: list
//    width: 180; height: 200

//// 1、 基本数据类型
////    model:  3                    // 数字类型，也可以list 类型  控制了所有数据
////    delegate: Button {             // 控制每一项数据是如何绘制的
////        text: index
////    }
////    spacing: 10                 // 每项之间的间隔

//// 2、数组类型
////    model: ["aaa", "bbb", "ccc"]
////    spacing: 20
////    delegate: Rectangle {
////        Text {
////            text: modelData
////        }
////    }

//// 3、复杂数据类型
//    model: ListModel {                         // 复杂结构对象
//        ListElement {                          // list 元素，元素当中可以添加更多属性
//            name: "Bill Smith"                 // ListView 中可以直接访问元素，不能使用 modelData
//            number: "555 3264"
//            myicon: "qrc:/th.jpg"
//        }
//        ListElement {
//            name: "John Brown"
//            number: "555 8426"
//            myicon: "qrc:/th.jpg"
//        }
//        ListElement {
//            name: "Sam Wise"
//            number: "555 0473"
//            myicon: "qrc:/th.jpg"
//        }
//    }

//// 普通绘制成 button
//    spacing: 50
////    delegate: Button {
////        text: name + " " + number
////        Image {source: myicon; width: 20; height: 20 }            // 这样加载图片
////    }

//// 选中高亮绘制
//    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }    // 高亮实现，配合delegate: Rectangle
//    delegate: Rectangle {
//        color : "transparent"
//        width: list.width
//        height: 50
//        Text { id: txt; text: name + " " + number }
//        Image {source: myicon; width: 20; height: 20 }            // 这样加载图片

//        MouseArea {                                               // 点击区域
//            anchors.fill: parent
//            onClicked: {
//                console.log("list current index:", list.currentIndex, "index:", index)                    // currentIndex 当前 delegate 高亮项, index 点击的项
//                list.currentIndex = index                                                                     // 赋值后切换
//            }
//        }
//    }
//}

//// 2、上下方添加控件
//Rectangle {
//    id: rect
//    width: 180
//    height: 200
//    border.color: "black"
//    anchors.centerIn: parent

//    ListView {
//        id: list
//        width: 180; height: 200

//        header: Rectangle {                       // listview 上方添加控件
//            width: list.width
//            height: 20
//            color: "yellow"
//        }

//        footer: Rectangle {                      // ListView 下方添加控件
//            width: list.width
//            height: 20
//            color: "red"
//        }

//        model: ListModel {                         // 复杂结构对象
//            ListElement {                          // list 元素，元素当中可以添加更多属性
//                name: "Bill Smith"                 // ListView 中可以直接访问元素，不能使用 modelData
//                number: "555 3264"
//                myicon: "qrc:/th.jpg"
//            }
//            ListElement {
//                name: "John Brown"
//                number: "555 8426"
//                myicon: "qrc:/th.jpg"
//            }
//            ListElement {
//                name: "Sam Wise"
//                number: "555 0473"
//                myicon: "qrc:/th.jpg"
//            }
//        }

//        spacing: 10
//        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
//        delegate: Rectangle {
//            color : "transparent"
//            width: list.width
//            height: 20
//            Text { id: txt; text: name + " " + number }
//            Image {source: myicon; width: 20; height: 20 }            // 这样加载图片

//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    console.log("list current index:", list.currentIndex, "index:", index)                    // currentIndex 当前 delegate 高亮项, index 点击的项
//                    list.currentIndex = index                                                                     // 赋值后切换
//                }
//            }
//        }
//    }
//}

//// 3、
Rectangle {
    id: rect
    width: 180
    height: 200
    border.color: "black"
    anchors.centerIn: parent

    ListView {
        id: list
        width: 180; height: 200

        model: ListModel {                         // 复杂结构对象
            ListElement {                          // list 元素，元素当中可以添加更多属性
                name: "Bill Smith"                 // ListView 中可以直接访问元素，不能使用 modelData
                number: "555 3264"
                myicon: "qrc:/th.jpg"
            }
            ListElement {
                name: "John Brown"
                number: "555 8426"
                myicon: "qrc:/th.jpg"
            }
            ListElement {
                name: "Sam Wise"
                number: "555 0473"
                myicon: "qrc:/th.jpg"
            }
        }

        spacing: 10
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        delegate: Rectangle {                   // 控制每一个数据如何绘制
            color : "transparent"
            width: list.width
            height: 20
            Text { id: txt; text: name + " " + number }
            Image {source: myicon; width: 20; height: 20 }            // 这样加载图片

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("list current index:", list.currentIndex, "index:", index)                    // currentIndex 当前 delegate 高亮项, index 点击的项
                    list.currentIndex = index                                                                     // 赋值后切换
                }
            }
        }

        Component {
            id: sectionHeading
            Rectangle {
                width: list.width
                height: 20
                //color: "lightsteelblue"

                Text {
                    text: section
                    font.bold: true
                    font.pixelSize: 20
                }
            }
        }
        section.property: "name"                    // 选择 name 属性
        section.criteria: ViewSection.FullString    // 可以设置显示完整字符串或者单个字符
        section.delegate: sectionHeading            // 对应每一个 section.property 如何绘制
        boundsBehavior: Flickable.StopAtBounds      // 设置为 stop 后拖动不可回弹
    }

}
