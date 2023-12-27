import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 700
    height: 700
    title: qsTr("Hello World")

    Rectangle {
        id: container;
        width: 700
        height: 700
        function goForIt(parent) {
            parent.x = (Math.floor(Math.random()*600));
            parent.y = (Math.floor(Math.random()*600));
            bounceAnimation.start();
        }

        Text {
            id: head;
//            source: "vlad.png";
            text: "aaa"
            color: "red"
            anchors.centerIn: parent
            font.pixelSize: 18

            MouseArea {
                anchors.fill: parent
                onClicked: {container.goForIt(parent);}
            }
            Behavior on x {
                PropertyAnimation {
                    target: head;
                    properties: "x";
                    duration: 1000;
                }
            }
            Behavior on y {
                PropertyAnimation {
                    target: head;
                    properties: "y";
                    duration: 1000;
                }
            }

            transform: Scale {
                id: scaleTransform
                property real scale: 1
                xScale: scale
                yScale: scale
            }

            SequentialAnimation {
                id: bounceAnimation
                loops: 1
                PropertyAnimation {
                    target: scaleTransform
                    properties: "scale"
                    from: 1.0
                    to: 2.0
                    duration: 500
                }
            }
        }
    }
}
