import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//// 1、使用 itemAt() 访问由Repeater （model）  构造的子项
//    Repeater {
//        id: rep
//        model: 3
//        Button {
//            id: btn
//            y: index * 60
//            text: "btn" + index
//        }
//    }

//    Button {
//        id: btn2
//        x: 200
//        text: "clicked"
//        onClicked: {
////            console.log(rep.itemAt(0).text  )      // model 创建的内容不能用id 找到，需要用 itemAt(x )
//            for(var i = 0; i < rep.count; i++) {     // 输出所有rep 下子项的内容
//                console.log(rep.itemAt(i).text)
//            }
//        }
//    }

//// 2、获取 column 中所有子项，并过滤获取
//    Column {
//        id: col
//        Button {
//            id: btn
//            text: "btn"
//        }

//        Text {
//            id: txt
//            text: "aaa"
//        }

//        Rectangle {
//            id: rect
//            width: 100
//            height: 200
//            color: "black"
//        }
//        spacing: 20
//    }

//    Button {
//        id: btn2
//        x: 200
//        text: "clicked"
//        onClicked: {
//            for (var i = 0; i < col.children.length; i++) {         // 通过 col.children.length 获取 col 中子项目数量
//                //console.log(col.children[i].text)
//                console.log(col.children[i] instanceof Button)      // 通过 instanceof 来过啦项目
//            }
//        }
//    }

//    Column {
//        id: col
//        Repeater {
//            id: rep
//            model: 3
//            Button {
//                id: btn
//                text: "btn" + index
//            }
//        }

//        Text {
//            id: txt
//            text: "aaa"
//        }

//        Rectangle {
//            id: rect
//            width: 100
//            height: 200
//            color: "black"
//        }
//        spacing: 20
//    }

//    Button {
//        id: btn2
//        x: 200
//        text: "clicked"
//        onClicked: {
//            for (var i = 0; i < col.children.length; i++) {         // 如果 col 里面有 Repeater ，里面有3个button 实际是4个控件, 这个遍历可以遍历子子控件
//                //console.log(col.children[i].text)
//                console.log(col.children[i] instanceof Button)      // 通过 instanceof 来过啦项目
//            }
//        }
//    }

//// 3、获取 ListView 子项
    ListView {
        id: list
        width: 100
        height: 200
        model: ["aaa", "bbb", "ccc"]

        delegate: Text {            // 如果 delegate 中是其他复杂子项，则用上面相应的方法，再次遍历
            id: txt
            text: modelData
        }
    }

    Button {
        id: btn2
        x: 200
        text: "clicked"
        onClicked: {
            console.log(list.contentItem.children[0])
            for (var i = 0; i < list.contentItem.children.length; i++) {      // contentItem 控制list 绘制
                console.log(list.contentItem.children[i].text)                // 会多一个 contentItem
                //console.log(list.contentItem.children[i] instanceof Button)    // 通过 instanceof 来过啦项目
            }
        }
    }

}
