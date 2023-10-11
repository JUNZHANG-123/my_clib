import QtQuick 2.0
pragma Singleton			// 表明这个文件在实例化时只能有一个实例

QtObject {
    property int screenHeight: 960
    property int screenWidth: 640
 
    property int myPixelSize: 28
    property string textColor: "red"
}
