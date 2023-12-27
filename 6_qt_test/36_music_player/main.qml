import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 400
    height: 100
    title: qsTr("Hello World")

    Text{
        id: mt
        anchors.centerIn: parent
        visible: false
        color: "red"
        text:"曾经年少爱追梦，一心只想往前飞。"
        font.pixelSize: 24
     }

     PropertyAnimation{
        target: mr1
        property: "width"
        from: 0
        to: m2.width
        duration: 5000
        loops: -1
        running: true
     }

     Rectangle{
         id: m2
         anchors.fill: mt
         color:"#00000000"
         Rectangle{
             id: mr1
             height:parent.height
             color: "blue"

             onWidthChanged: {
                console.log(width)
             }
             //width是从0到m2.width
         }
//         Rectangle{
//             x: mr1.width  //从0到m2.width
//             height:parent.height
//             width: m2.width-mr1.width
//             color: "red"
//         }
     }

     ShaderEffectSource {
        id: mask
        visible: false
        anchors.fill: mt
        hideSource : true
        sourceItem: m2
     }

     Blend {
       anchors.fill: mt
       source: mt
       foregroundSource: mask
       mode: "color"
    }
}

