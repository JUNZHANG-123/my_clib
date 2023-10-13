# qml 学习记录要点整理



## 创建qml 工程

新建 -> Application -> Qt Quick Application - Empty



## 01_qml_helloworld

1、window 常用属性介绍

?		focus  焦点   visible 可见度  opacity 透明度  objectName 控件名称  id 控件id  color 控件颜色  x/y 控件相对于父控件偏移 title 标题  width/heigth 宽高

2、怎么固定界面宽高

?		minimumWidth/minimumHeight   maximumWidth/maximumHeight  设置成一样的

3、信号和槽函数基本介绍



## 02_qml_item_and_rectangle

1、z 轴

2、 控件需要接收键盘或其他信息时，需要将当前控件设置为焦点、

3、Keys.onReturnPressed  回车键

4、绝对坐标设置示例 x: rect1.width +20 

5、anchors/锚 布局

Anchors provide a way to position an item by specifying its relationship with other items.

锚提供了一种通过指定项目与其他项目的关系来定位项目的方法



Margins apply to top, bottom, left, right, and fill anchors. 边距适用于上、下、左、右和填充锚

 The anchors.margins property can be used to set all of the various margins at once, to the same value.

anchors.margins 属性可用于一次将所有不同的边距设置为相同的值

It will not override a specific margin that has been previously set to clear an explicit margin set its value to undefined. 

它不会覆盖先前设置的特定边距;若要清除显式边距，请将其值设置为未定义

Note that margins are anchor-specific and are not applied if an item does not use anchors.

请注意，边距是锚定的，如果项目不使用锚定，则不应用边距

Offsets apply for horizontal center, vertical center, and baseline anchors.

偏移量适用于水平中心、垂直中心和基线锚点。



?		anchors.fill: parent    填充满父控件

上下左右对其

?		anchors.top : AnchorLine/锚线
?		anchors.bottom : AnchorLine
?		anchors.left : AnchorLine
?		anchors.right : AnchorLine

横列居中

?		anchors.horizontalCenter : AnchorLine
?		anchors.verticalCenter : AnchorLine

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter



基于父控件居中

?		anchors.centerIn: parent

对齐边距（**注意：左右页边距使用要设置完x 锚点后才生效，上下页边距y锚点**）

?		anchors.margins : real				// 一起设置
?		anchors.topMargin : real			// 单独设置
?		anchors.bottomMargin : real
?		anchors.leftMargin : real
?		anchors.rightMargin : real



6、rotation 旋转   scale 缩放

7、Rectangle 基本参数

//        antialiasing: true          // 抗锯齿，曲线中才有差别
//        border.color: "red"         // 边框，整个控件宽度没有改变，只是往内部缩
//        border.width: 30
//        radius: 15                  // 圆角弧度

8、Rectangle gradient 颜色渐变： gradient



## 03_qml_rectangle_bordor

1、建立自己的控件 MyRectangle，建立一个新文件MyRectangle.qml，在 main.qml 中调用

2、MyRectangle 中设置变量 myTopMargin/myButtomMargin，由 main.qml 中传入 MyRectangle ，从而改变anchors.topMargin/anchors.bottomMargin 值

3、实现边框只显示部分



## 04_qml_states_and_transitions

1、states 控件属性状态机使用，鼠标点击/释放后修改控件属性

2、动画效果未实验，版本问题



## 05_qml_component_and_loader

1、Component 类似容器，可以包含所有控件，被包含的控件包含Component.onCompleted/ Component.onDestruction 创建完成/销毁槽函数

2、被 Component 包含的内容不能直接显示，需要用loader 控件显示

3、Loader 可以 source qml文件，或者使用 sourceComponent 加载 Componpent

4、Loader 可使用 onStatusChanged 查看加载控件的状态变化，打开asynchronous 后，会增加loading 状态，值为2

5、使用 loader.sourceComponent = null  可销毁控件，source 应该类似

6、其他地方要修改loader 里面控件值，需要用 loader.item. 才能访问

7、图片加载使用 

```
////        Image {                     // 加载静态图像
////            id: img
////            source: "/th.jpg"
////            width: 50               // 调整大小，缩放
////            height: 50
////        }
//        AnimatedImage {               // 加载动态图像
//            id: img
//            source: "/th2.gif"

//        }
```



## 06_qml_mouseArea

1、mouseArea 基本属性介绍

2、拖拽 drag 属性介绍

3、注意，所有onXXX 槽函数响应表明有对应属性改变



## 07_qml_button

1、checked 属性，默认false，如果为true 则表示默认选择，则高亮显示

2、checkable 表示改按钮可以可以被选中

3、checkable 为true，并且设置 autoExclusive 为true，则所有同级按钮只会选中1个

4、autoRepeat  为true 后会重复响应按键实际

5、使用 indicator 加载图片，一般不使用

6、使用 text 给按钮加上文字，一般不使用

7、测试 DelayButton / RadioButton / switch / tab

8、使用 ButtonGroup 来设置button 属性集合，设置给对应控件中的button 使用

9、**自定义按键使用 background  来调整背景及按键其他属性，使用 contentItemcontentItem 来对内容重绘**



## 08_qml_property

1、基础类型介绍

?		int / real / string / color / url

2、property 可以定义所有组件

?		property Component mycom

3、不知道对方类型时，可使用 var 

4、list 类似数组

5、属性前加 readonly 表示该属性只读

6、外部使用必须赋值，加 required

7、外部要访问子控件，可以用 property alias 给控件或者控件中某个属性取别名，来进行访问

8、提示 Invalid property name “xxx“ M16，可以在报错语句上方加上

```
// @disable-check M16
```



## 09_qml_checkbox

1、使用 ButtonGroup + Column 实现 checkBox 排他

2、Button 中 设置 ButtonGroup，实现排他

3、tristate: true             // 3态 √ - 空



## 10_qml_text

1、基本属性介绍

2、超出控件长度部分使用省略号

3、text 字段支持html / 富文本 / 纯文本

4、字体单词自动换行

```
//            wrapMode: Text.WordWrap     // 自动单词换行
//            anchors.fill: parent
//            elide: Text.ElideRight
```

5、超链接，配合 MouseArea 做页面加载



## 11_qml_popup_overlay

1、弹窗基本使用，使用 contentItem 自定义 popup

2、popup 例外



## 12_qml_repeater

1、repeater 使用



## 13_qml_listview

1、listview 可以定义普通数据类型，如int 或者数组，和复杂数据类型；普通数据类型使用 modelData 获取属性；

2、复杂数据类型使用 model: ListModel {ListElement{}} 定义， ListElement 表示ListModel 中包含的元素，元素中可以有多个属性；ListElement 元素中的属性，ListView 中可以直接访问元素，不能使用 modelData；

3、ListView 中，通过 delegate 使用 model 中的属性内容，控制每一项控件绘制

4、通过 spacing 设置每一项控件间隔

5、highlight: Rectangle { color: "lightsteelblue"; radius: 5 }    // 高亮实现，高亮实现中，delegate: 必须使用 Rectangle {}

6、ListView 中使用header/ footer 实现添加外部上下方添加控件

7、使用 section + Component 实现单独绘制一行，类似章节标题目录

        Component {
            id: sectionHeading
            Rectangle {
                width: list.width
                height: 20
                //color: "lightsteelblue"
    
                Text {
                    text: section
                    font.bold: true
                    font.pixelSize: 20
                }
            }
        }
        
        section.property: "name"                    // 选择 name 属性
        section.criteria: ViewSection.FullString    // 可以设置显示完整字符串或者单个字符
        section.delegate: sectionHeading            // 对应每一个 section.property 如何绘制
        boundsBehavior: Flickable.StopAtBounds      // 设置为 stop 后拖动不可回弹



## 14_qml_combobox

1、model 设置有多少个combo box

2、editable: true                      // 可编辑使能       ； count 可以获取 combo box 个数

3、编辑输入后，添加一个 combo box，包含

```
//    onAccepted: {                               // 回车键后触发
//        if (find(editText) === -1)              // 查找当前可编辑文本 是否已存在
//            model.append({text: editText})      // append 添加一个新的 ListElement
//    }
```

4、获取当前combo box 内容

```
//    onCurrentTextChanged: {
//        console.log(currentText)
//    }
```

5、使用 validator 限制输入合法性

6、自定义 ComboBox 实现，包括 Rectangle 中 阴影设置 layer.effect: DropShadow



## 15_qml_focus

1、focus 基本介绍

```
focusPolicy: Qt.NoFocus                             // 设置为 Qt.NoFocus 则无法获取焦点，但是还是可以通过 forceActiveFocus()  设置焦点
```

2、多个控件同时获取 focus ，后构造的focus 会获取到焦点；文件后面的控件会先构造，比如下面 txt2 会先构造

3、focusReason)      // 获取 focus 原因

4、//// 3、FocusScope 控件的子控件都能获取到焦点，focus 为true； FocusScope控件设置了 focus 则子控件的 focus 设置可以让 activeFocus 也为 true
//// 简单逻辑用 focus 设置为true 没问题，但是复杂控件，需要用 activeFocus



## 16_qml_signal

1、signal 和槽函数基本使用，对应3中槽函数绑定方法

2、对于异步加载组件，事件通过自定义信号传递示例：使用 Component 将控件 的click 信号传到外部控件中，在外部控件的 loader 中接收



## 17_qml_c++ 交互基础

![image-20231005093819523](C:\Users\90952\AppData\Roaming\Typora\typora-user-images\image-20231005093819523.png)



1、c++ 中通过 设置全局变量，给qml 中使用

    QQmlContext* context = engine.rootContext();
    QScreen *screen = QGuiApplication::primaryScreen();             // 获取屏幕属性
    QRect rect = screen->virtualGeometry();                         // 获取屏幕宽度
    //context->setContextProperty("SCREEN_WIDTH", rect.width());      // SCREEN_WIDTH  为全局对象
    context->setContextProperty("SCREEN_WIDTH", 640);

2、子控件中直接定义的属性，相当于 public 变量，父控件可以直接访问

3、子控件中通过 QtObject 定义的变量，自己内部可以通过 id. 方式访问，外部可以通过取别名方式范围；这种方式c++ 无法访问

    QtObject {
        id: attributes                // 外部要访问可以给这个控件取别名
        property int testValue: 0     // 定义在这相当于 private
    }
    
    Component.onCompleted: {
        console.log(attributes.testValue)       // 可以用 attributes.testValue 放松访问 property int testValue
    }
    
    property alias attr: attributes   // 给 attributes 取别名后，外部可以通过 attr 访问(获取/设置)



4、通过 qmlRegisterType 设置全局类给qml 中使用

    // 注册当前类型，在QML 中就可以访问，"MyObj" 是要引入的类名称，后面是版本号，最后是控件名
    qmlRegisterType<MyObect>("MyObj", 1, 0, "MyObect"); //我们一定要通过创建对象来定义一个我们自定义的object

其中，绑定操作可以在qml 中，也可以在c++ 中，信号可以定义在qml 中也可以定义在c++中



## 18_qml_cpp_qmlRegisterSingletonType

1、使用 qmlRegisterSingletonType 实现全局单例创建

    // 全局单例例子，实现后 qml 类中可以直接用类名访问
    // 单例的好处是不用在qml 创建该obj
    qmlRegisterSingletonType<MyObject>("MyObj", 1, 0, "MyObject", MyObject::getInstance);

其中，绑定操作可以在qml 中，也可以在c++ 中，信号可以定义在qml 中也可以定义在c++中



## 19_qml_cpp

1、使用 QMetaObject::invokeMethod 在c++ 端调用qml 中的函数



## 20_qml_qmlRegisterUncreatableMetaObject

1、使用 qmlRegisterUncreatableMetaObject ，如果创建会报错，提示是最后一个参数

    // 注册一个类型，qml 中不能创建实例，只能访问第五个参数访问枚举
    qmlRegisterUncreatableMetaObject(MyObject::staticMetaObject, "MyObj", 1, 0, "MyObject", "Access to enums & flags only");



## 21_qml_layout

1、Column / Row / Flow 使用

2、点击按钮创建按键，自动 Column 布局

3、布局动画 move / add / populate



## 22_qml_grid_opacitymask

1、Grid 和 OpacityMask 配合使用，OpacityMask 可以将2个图层合并

2、anchors.fill: parent 后怎么显示父控件外框；怎么固定一端

    Rectangle {
        width: grid.width + 4
        height: grid.height +4      // 往外扩大 4 pixel
        border.color: "red"
        border.width: 3
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter       // 通过这2行可以固定一端位置，如果减掉高度，底部也会对齐
        anchors.bottom: parent.bottom
    
        OpacityMask {               // 子控件会覆盖父控件
            source: grid            // 合并源
            maskSource: maskRect    // 遮盖源
            anchors.fill: parent
            anchors.margins: 2      // 往内收缩2 pixel
        }
    }

3、怎么减小 Repeater 绘制开销



## 23_qml_find_subobject

1、使用 itemAt() 访问由Repeater （model）  构造的子项

2、通过 col.children.length 获取 Column中子项目数量

3、通过  contentItem 获取 ListView 中子项



## 24_qml_timer

qml timer 使用



## 24_qml_user_model

1、新建 qt item model -> QAbstractListModel 建立自定义c++ 类

2、c++ 中设置枚举（key），通过 rowCount 告诉qml model 有几个元素；通过 roleNames 建立c++ 和qml 映射， 字符串和枚举的映射，枚举c++定义即key，字符串，qml中使用； 最后通过 data 建立 key 对应数据内容返回的具体实现。



## 25_qml_user_model

传结构体



## 26_qml_listview2

1、SwipeView 介绍

2、自定义 SwipeView 效果，使用 ObjectModel 自定义加载内容给 ListView

3、使用 XmlListModel ，获取 xml 中数据，传递给 ListView



## 27_qml_qdatastream

保留



## 28_qml_cpp_QString

1、使用 QList<QString> 建立一个list 数组；使用 QListIterator<QString> iter(list) 遍历取出数组

2、使用 list.join

3、split 分割，for 循环

4、// 打开文件 QFile file(":/test.txt");



## 29_qml_textedit

将 TextEdit 的 text 取别名引出，外部可输入

```
FocusScope {
    width: 96; height: 96
    Rectangle {
        anchors.fill: parent
        color: "lightsteelblue"
        border.color: "gray"
    }
    property alias text: input.text
    property alias input: input
    TextEdit {
        id: input
        anchors.fill: parent
        anchors.margins: 4
        focus: true
    }
}
```



## 30_qml_key_element

```
    // 通过按键上下左右 可以移动按键
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
```



## 31_qml_qmldir_test

利用 singleton  来集中定义在一个文件中，从而被所有的模块所使用。

这样的方法同样适合我们style我们的应用。我们在一个地方修改设置，但是在所有的模块中都使用。

这类似于C/C++中定义一些常量，在不同的.cpp文件中使用一样。

**Settings.qml**

```
pragma Singleton
import QtQuick 2.0
 
QtObject {
    property int screenHeight: 960
    property int screenWidth: 640
 
    property string textSize: "x-large"
    property string textColor: "red"
}
```

首先，我们可以看到我们在文件的开始部分使用了pragam Singleton，表明这个文件在实例化时只能有一个实例。

另外，我们必须在我们应用的根目录下添加如下的 **qmldir** 文件：

```
singleton Settings 1.0 Settings.qml
```

参考： [QML Styling 及 Singleton 使用方法浅谈_qml singleton-CSDN博客](https://blog.csdn.net/ubuntutouch/article/details/46980635)



## 32_qml_flickable

使用 Flickable 来实现 page 功能，可以上下滑动；



## 33_qml_createObject

1、使用 Component.createObject  来动态创建

2、定义一个数组来维护销毁动态创建的组件



```
   property var itemCells: new Array  
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
```



参考： [05动态创建QML对象_qml createobject-CSDN博客](https://blog.csdn.net/u013064585/article/details/108350797)









