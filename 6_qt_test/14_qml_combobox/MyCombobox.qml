import QtQuick 2.6
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

//// 1、下拉菜单控件
//ComboBox {
//    id: combox

//    //model: 3
//    model: ['a', 'b', 'c']

//    Component.onCompleted: {
//        console.log(count)              // count 有多少个样式
//    }

//    editable: true                      // 可编辑使能
//}


//// 2、可编辑后，追加一个控件
//ComboBox {
//    editable: true                      // 可编辑
//    model: ListModel {
//        id: model
//        ListElement {text: "a"}
//        ListElement {text: "b"}
//        ListElement {text: "c"}
//    }
//    onAccepted: {                               // 回车键后触发
//        if (find(editText) === -1)              // 查找当前可编辑文本 是否已存在
//            model.append({text: editText})      // append 添加一个新的 ListElement
//    }
//}

//// 3、currentText
//ComboBox {
//    id: combox
//    model: ['a', 'b', 'c']
//    onCurrentTextChanged: {
//        console.log(currentText)
//    }

//}

//// 4、用 validator 限制输入合法性
//ComboBox {
//    model: 10
//    editable: true
//    validator: IntValidator {       // 限制输入范围
//        top: 9
//        bottom: 0
//    }
//    onAcceptableInputChanged: {     // 验证当前输入是否匹配 validator
//        console.log(acceptableInput)
//    }
//}

//// 5、自定义 ComboBox
ComboBox {
      id: control
      width: 100
      height: 30
      model: ["First", "Second", "Third"]

      delegate: ItemDelegate {      // 针对 model 中每一个项具体绘制，ItemDelegate 可以当成button
          width: control.width
          contentItem: Text {       // 重新绘制 text 内容
              text: modelData
              color: index %2 ?"red":"blue"
              font: control.font
              elide: Text.ElideRight                // 过长省略
              verticalAlignment: Text.AlignVCenter
          }
          highlighted: control.highlightedIndex === index       // 选中高亮
      }

//      indicator: Canvas {           // 使用画布重新绘制 combobox 默认右边小图标
//          id: canvas
//          x: control.width - width - control.rightPadding
//          y: control.topPadding + (control.availableHeight - height) / 2
//          width: 12
//          height: 8
//          contextType: "2d"

//          Connections {
//              target: control
//              onPressedChanged: canvas.requestPaint()
//          }

//          onPaint: {
//              context.reset();
//              context.moveTo(0, 0);
//              context.lineTo(width, 0);
//              context.lineTo(width / 2, height);
//              context.closePath();
//              context.fillStyle = control.pressed ? "#17a81a" : "#21be2b";
//              context.fill();
//          }
//      }

      indicator: Image {        // 修改右边图标为图片
          id: img
          width: 30
          height: 30
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          source: "/th.jpg"
      }

      contentItem: Text {       // 重新绘制 当前控件显示内容
          leftPadding: 0
          rightPadding: control.indicator.width + control.spacing

          text: control.displayText                         // ComboBox displayText 显示文本
          font: control.font                                // ComboBox font 显示字体
          color: control.pressed ? "#17a81a" : "#21be2b"    // 点击变化颜色
          verticalAlignment: Text.AlignVCenter              // 居中
          elide: Text.ElideRight                            // 过长右侧省略
      }

      background: Rectangle {           // 只影响打开的控件背景
          implicitWidth: 120
          implicitHeight: 40
          border.color: control.pressed ? "#17a81a" : "#21be2b"
          border.width: control.visualFocus ? 2 : 1
          radius: 2
      }

      popup: Popup {                    // ComboBox 的 popup 只能是 Popup，绘制整个下拉控件 （delegate: ItemDelegate  中具体每项绘制）
          y: control.height - 1         // 下拉窗体和 ComboBox 距离，如果是顶部则自动往下弹出，如果是底部则自动往上弹出， 如果外部给一个 Rectangle 则可以实现控制
          width: control.width
          implicitHeight: contentItem.implicitHeight
          padding: 1

          contentItem: ListView {
              clip: true
              implicitHeight: contentHeight
              model: control.popup.visible ? control.delegateModel : null
              currentIndex: control.highlightedIndex

              //ScrollIndicator.vertical: ScrollIndicator { }     // 下拉窗体右侧 滚动条
              ScrollBar.vertical: ScrollBar{policy: ScrollBar.AlwaysOn}                     // 默认鼠标悬停或拖动显示
              interactive: true                                  // 设置为false 则不可拖动
              boundsBehavior: Flickable.StopAtBounds             // 设置为 stop 后拖动不可回弹
          }

          background: Rectangle {           // 影响下拉控件背景
              border.color: "#21be2b"       // 下拉弹窗外框
              radius: 2
              layer.enabled: true           // 使用 layer + DropShadow 来设置阴影
              layer.effect: DropShadow {
                  horizontalOffset: 3       // 横向偏移
                  verticalOffset: 3         // 纵向偏移
                  radius: 8.0               // 模糊程度
                  samples: 17               // 只越大模糊效果越好，开销越大
                  color: "#80000000"        // 模糊区域颜色
              }
          }
      }
  }





