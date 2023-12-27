import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListModel {
        id:navimodel
    }

    ListView {
        id:naviView
        spacing: 28
        anchors.fill: parent        // 要足够大，子项才能显示，不然会被剪切掉
        model: navimodel
        focus: true
        orientation: ListView.Vertical
        delegate: Item {
            id:naviItem
            width: 120;
            height: 40
            Column {

                Item{
                    Text {
                        id:content
                        text: naviName
                        width: 120
                        //font.styleName: "Bold"
                        font.pixelSize: 24
                        //textFormat: Text.PlainText
                        renderType: Text.QtRendering
                        horizontalAlignment: Text.AlignHCenter
                        color: naviItem.ListView.isCurrentItem ? "#FF12CFA7" : "red"        //
                    }

                    Rectangle{
                        id:line
                        anchors.left: parent.left
                        anchors.leftMargin:(naviItem.width - 20)/2
                        anchors.top:content.bottom
                        anchors.topMargin: 8
                        color: "#FF12CFA7"
                        width: 20
                        height: 3
                        radius: 1
                        visible: naviItem.ListView.isCurrentItem ? true : false
                    }
                }
            }

            MouseArea{
                anchors.fill: parent

                onClicked:
                {
                    naviView.currentIndex = index       // 赋值
                    if(naviName === qsTr("牛津"))        // 可以直接用id 来判断是否点击到该 Item
                    {
                        console.log("牛津")
                        return;
                    }

                    if(naviName === qsTr("作业帮"))
                    {
                        console.log("作业帮")
                        return;
                    }

                    if(naviName === qsTr("精讲"))
                    {
                        console.log("精讲")
                        return;
                    }
                }
            }
        }
    }

    MyItem {
        id: item
        x: 200
        onAddNavBtn: {
            naviView.model.clear();                 // 先清空所有元素

            console.log("onAddNavBtn length:", navData.length)

            for(var i  = 0; i < navData.length; ++i)
            {
                navimodel.append(navData[i]);       // 向 ListModel 中追加元素
            }
        }
    }

}
