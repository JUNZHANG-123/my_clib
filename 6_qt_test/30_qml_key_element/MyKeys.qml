import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    width: 400; height: 200
    color: "gray"

    Rectangle {
        id: square
        width: 50
        height: 50
        color: "green"
    }

    focus: true
    // 上下左右 可以移动按键
    Keys.onLeftPressed: square.x -= 8
    Keys.onRightPressed: square.x += 8
    Keys.onUpPressed: square.y -= 8
    Keys.onDownPressed: square.y += 8

    Keys.onPressed: {
        switch(event.key) {             // 加减放大缩小按键
            case Qt.Key_Plus:
                square.scale += 0.2
            break;
            case Qt.Key_Minus:
                square.scale -= 0.2
            break;
        }
    }
}
