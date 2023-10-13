import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property var itemCells: new Array

    Component{
        id:com
        MyItem {

        }
    }

    Component.onCompleted: {
        var cellCount = itemCells.length
        for(var i = 0;i < cellCount;i++){
            itemCells.pop().destroy();
        }

        itemCells.push(com.createObject(root,{width: 300}))     // 动态创建，并通过 itemCells 管理销毁

    }

    Component.onDestruction: {
        console.log("ZybEnchDictControl++++++++++++++++++++++++++++++++++")
        var cellCount = itemCells.length
        var cell;
        for(var i = 0;i < cellCount;i++){
            cell = itemCells.pop()
            cell.parent = null
            cell.destroy();
        }

    }
}
