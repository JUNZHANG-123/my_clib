import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Window {
    visible: true
    width: 900
    height: 480
    title: qsTr("Hello World")

    Audio
    {
        id : player
        autoPlay: true
        onSourceChanged:
        {
            //console.log("cur source =",source)
        }

        onError:
        {
            console.log("onError",playBtn.source.toString())
            console.log("onError",error)
            console.log("onError",errorString)
        }

        onStatusChanged:
        {
            console.log("onStatusChanged", status)
            switch(status)
            {
            case 7:
                console.log("play over",playBtn.source.toString());
                break
            }
        }

        onPositionChanged: {
        }
    }


    Rectangle
    {
        width: parent.width
        height: 95
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        border.color: "red"
        color: "transparent"

        Text {
            id: curTime
            text: currentTimeMMSS(player.position)
            color: "#242D25"
            font.pixelSize: 20
            anchors.left: parent.left
            anchors.leftMargin: 40
            horizontalAlignment: Text.AlignRight
            anchors.verticalCenter: parent.verticalCenter
        }

        Slider
        {
            id:timeSpan
            orientation: Qt.Horizontal
            from: 0
            value: player.position
            to:player.duration
            stepSize: 1
//            implicitWidth: 771
            anchors.left: curTime.right
            anchors.leftMargin: 12
            anchors.verticalCenter: curTime.verticalCenter

            background: Rectangle {
                x: timeSpan.leftPadding
                y: timeSpan.topPadding + timeSpan.availableHeight / 2 - height / 2
                implicitWidth: 500
                implicitHeight: 7
                width: timeSpan.availableWidth
                height: implicitHeight
                radius: implicitHeight/2
                color: "#330A996F"

                Rectangle {
                    width: timeSpan.visualPosition * parent.width
                    height: parent.height
                    color: "#0A996F"
                    radius: 2
                }
            }

            onPressedChanged:
            {
                console.log("onPressedChanged",pressed)

                if(!pressed)
                {
                    player.seek(timeSpan.value)
                    console.log("player.seek",timeSpan.value,player.status,player.playbackState, player.seekable);
                    console.log("player.seek",timeSpan.value,player.position, player.duration);
                }
            }

            onMoved: {
                console.log("onMoved", timeSpan.value)
//                curTime.text = UILogic.currentTimeMMSS(timeSpan.value)
            }

            handle: Rectangle {
                x: timeSpan.leftPadding + timeSpan.visualPosition * (timeSpan.availableWidth - width)
                y: timeSpan.topPadding + timeSpan.availableHeight / 2 - height / 2
                implicitWidth: 25
                implicitHeight: 25
                radius: 13
                color: "#0A996F"
            }
        }

        Text {
            id: totalTime
            text: currentTimeMMSS(player.duration)
            color: "#242D25"
            font.pixelSize: 20
            anchors.left: timeSpan.right
            anchors.leftMargin: 12
            anchors.verticalCenter: curTime.verticalCenter
        }
    }

    Rectangle
    {
        id: btn1
        color: "red"
        width: 50
        height: 50
        x:0
        y:0

        MouseArea {
            anchors.fill: parent
            onClicked: {
                player.source = "https://iotcdn.cdnjtzy.com/iot-server/system/resource/2023/11/01/7fdf129e050f43f8a60573991b898588258.MP3"
                player.playbackRate = player.playbackRate+0.5
                console.log("onClicked", player.playbackRate)

            }


        }

    }

    function currentTimeMMSS(time)
    {
        var sec= Math.floor(time/1000);
        var hours=Math.floor(sec/3600);
        var minutes=Math.floor((sec-hours*3600)/60);
        var seconds=sec-hours*3600-minutes*60;
        var hh,mm,ss;
        if(hours.toString().length<2)
            hh="0"+hours.toString();
        else
            hh=hours.toString();
        if(minutes.toString().length<2)
            mm="0"+minutes.toString();
        else
            mm=minutes.toString();
        if(seconds.toString().length<2)
            ss="0"+seconds.toString();
        else
            ss=seconds.toString();

    //    return hh + ":" + mm+":"+ss;
        if(hh !== "00")
        {
            return hh + ":" + mm+":"+ss;
        }
        else
        {
            return mm+":"+ss;
        }

    }


}
