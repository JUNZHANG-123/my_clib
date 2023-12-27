import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: root
    width: 100
    height: 100
    signal addNavBtn(var navData);

    function setChDictData() {
        var naviData = new Array;

        naviData.push({"naviName": qsTr("精讲")})     // naviName 在 外部使用
        naviData.push({"naviName": qsTr("作业")})
        naviData.push({"naviName": qsTr("牛津")})

        console.log("setChDictData")

        emit:addNavBtn(naviData);
    }

    Button {
        text: "start"
        onClicked: root.setChDictData()
    }


}
