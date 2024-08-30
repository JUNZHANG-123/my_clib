import QtQuick 2.0
//import QtMultimedia 5.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import "./"

Rectangle {
    id : listen_root
    color: "#FFE8FAD1"

    onVisibleChanged: {
        if (mainSwipeView.itemAt(menuList.currentIndex).getListModelCount() > 0) {
            mainSwipeView.itemAt(menuList.currentIndex).parentSta = listen_root.state
        }
    }
    
    MouseArea{
        anchors.fill: parent
        onPressed: {
        }
        onReleased: {
        }
        onClicked: {
        }
    }

    state: ""
    states: [
        State {
            name: "history"
            StateChangeScript {
                script: {
                    console.log("history state")
                    swipInit()
                    mainSwipeView.itemAt(0).color = "yellow"  //设置属性时，可能还没把item add进去
                }
            }
        },

        State {
            name: "syn_word"
            StateChangeScript {
                script: {
                    console.log("syn_word state")
                }
            }
        },

        State {
            name: "scene_example"
            StateChangeScript {
                script: {
                    console.log("scene_example state")
                }
            }
        }
    ]

    ListModel {
        id: topModel

        ListElement {
            name: "最近在听"
        }
        ListElement {
            name: "同步词书"
        }
        ListElement {
            name: "情景例句"
        }
    }

    ListView {
        id:menuList
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 100
        orientation: ListView.Horizontal        // 水平显示，默认是竖的

        model: topModel     //表示加入3个model，数据为name

        Component {
            id : unitDelegate
            Rectangle {
                id: uint
                width: content_text.paintedWidth+52
                height: parent.height
                color: listen_root.color
                opacity: uint.ListView.isCurrentItem? 0.8: 0.6

                Text {
                    id: content_text
                    text: name
                    color: "#FF000000"
                    width: parent.width
                    font.styleName: "Regular"
                    font.pixelSize: 20
                    anchors.top: parent.top
                    anchors.topMargin: uint.ListView.isCurrentItem? 23: 28
                    anchors.right: parent.right
                }

                MouseArea
                {
                    id:mouseArea
                    anchors.fill: parent
                    onClicked:
                    {
                        menuList.currentIndex = index
                        mainSwipeView.contentItem.highlightMoveDuration = 0 // 这个动画很重要，设置后点击上面的item 就不会出现翻页动画
                        mainSwipeView.setCurrentIndex(index);

                        console.log(content_text.text, content_text.paintedHeight+20,menuList.currentIndex)
                        switch(menuList.currentIndex)
                        {
                        case 0:
                            listen_root.state = "history"
                            break
                        case 1:
                            listen_root.state = "syn_word"
                            break
                        case 2:
                            listen_root.state = "scene_example"
                            break
                        }
                    }
                }
            }
        }

        onCurrentIndexChanged: {
            mainSwipeView.contentItem.highlightMoveDuration = 0
            mainSwipeView.setCurrentIndex(currentIndex);
            switch(currentIndex)
            {
            case 0:
                listen_root.state = "history"
                break
            case 1:
                listen_root.state = "syn_word"
                break
            case 2:
                listen_root.state = "scene_example"
                break
            }
        }

        delegate: unitDelegate      //要画的控件，将会使用你 model 中的数据 name
        clip: true
    }

    Component {
        id:dynamicPageComponent

        Page1 {
            visible: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
        }
    }

    SwipeView
    {
        id: mainSwipeView
        anchors.top: menuList.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip:true

        onInteractiveChanged:
        {
            // console.log("mainSwipeView intrative",mainSwipeView.interactive)
        }

        onCurrentIndexChanged:
        {
            console.log("swipView onCurrentIndexChanged", menuList.currentIndex, currentIndex)
            menuList.currentIndex = currentIndex
        }
    }

    function swipInit()
    {
        if (mainSwipeView.count < 3)
        {
            var item;
            item = dynamicPageComponent.createObject(mainSwipeView, {color:"red"})
            mainSwipeView.addItem(item)

            item = dynamicPageComponent.createObject(mainSwipeView, {color:"black"})
            mainSwipeView.addItem(item)

            item = dynamicPageComponent.createObject(mainSwipeView, {color:"white"})
            mainSwipeView.addItem(item)
        }
    }

    Component.onCompleted:
    {
        console.log("onCompleted")
        swipInit();
    }

    Component.onDestruction:
    {
    }
}
