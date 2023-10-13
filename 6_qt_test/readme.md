# qml ѧϰ��¼Ҫ������



## ����qml ����

�½� -> Application -> Qt Quick Application - Empty



## 01_qml_helloworld

1��window �������Խ���

?		focus  ����   visible �ɼ���  opacity ͸����  objectName �ؼ�����  id �ؼ�id  color �ؼ���ɫ  x/y �ؼ�����ڸ��ؼ�ƫ�� title ����  width/heigth ���

2����ô�̶�������

?		minimumWidth/minimumHeight   maximumWidth/maximumHeight  ���ó�һ����

3���źźͲۺ�����������



## 02_qml_item_and_rectangle

1��z ��

2�� �ؼ���Ҫ���ռ��̻�������Ϣʱ����Ҫ����ǰ�ؼ�����Ϊ���㡢

3��Keys.onReturnPressed  �س���

4��������������ʾ�� x: rect1.width +20 

5��anchors/ê ����

Anchors provide a way to position an item by specifying its relationship with other items.

ê�ṩ��һ��ͨ��ָ����Ŀ��������Ŀ�Ĺ�ϵ����λ��Ŀ�ķ���



Margins apply to top, bottom, left, right, and fill anchors. �߾��������ϡ��¡����Һ����ê

 The anchors.margins property can be used to set all of the various margins at once, to the same value.

anchors.margins ���Կ�����һ�ν����в�ͬ�ı߾�����Ϊ��ͬ��ֵ

It will not override a specific margin that has been previously set to clear an explicit margin set its value to undefined. 

�����Ḳ����ǰ���õ��ض��߾�;��Ҫ�����ʽ�߾࣬�뽫��ֵ����Ϊδ����

Note that margins are anchor-specific and are not applied if an item does not use anchors.

��ע�⣬�߾���ê���ģ������Ŀ��ʹ��ê������Ӧ�ñ߾�

Offsets apply for horizontal center, vertical center, and baseline anchors.

ƫ����������ˮƽ���ġ���ֱ���ĺͻ���ê�㡣



?		anchors.fill: parent    ��������ؼ�

�������Ҷ���

?		anchors.top : AnchorLine/ê��
?		anchors.bottom : AnchorLine
?		anchors.left : AnchorLine
?		anchors.right : AnchorLine

���о���

?		anchors.horizontalCenter : AnchorLine
?		anchors.verticalCenter : AnchorLine

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter



���ڸ��ؼ�����

?		anchors.centerIn: parent

����߾ࣨ**ע�⣺����ҳ�߾�ʹ��Ҫ������x ê������Ч������ҳ�߾�yê��**��

?		anchors.margins : real				// һ������
?		anchors.topMargin : real			// ��������
?		anchors.bottomMargin : real
?		anchors.leftMargin : real
?		anchors.rightMargin : real



6��rotation ��ת   scale ����

7��Rectangle ��������

//        antialiasing: true          // ����ݣ������в��в��
//        border.color: "red"         // �߿������ؼ����û�иı䣬ֻ�����ڲ���
//        border.width: 30
//        radius: 15                  // Բ�ǻ���

8��Rectangle gradient ��ɫ���䣺 gradient



## 03_qml_rectangle_bordor

1�������Լ��Ŀؼ� MyRectangle������һ�����ļ�MyRectangle.qml���� main.qml �е���

2��MyRectangle �����ñ��� myTopMargin/myButtomMargin���� main.qml �д��� MyRectangle ���Ӷ��ı�anchors.topMargin/anchors.bottomMargin ֵ

3��ʵ�ֱ߿�ֻ��ʾ����



## 04_qml_states_and_transitions

1��states �ؼ�����״̬��ʹ�ã������/�ͷź��޸Ŀؼ�����

2������Ч��δʵ�飬�汾����



## 05_qml_component_and_loader

1��Component �������������԰������пؼ����������Ŀؼ�����Component.onCompleted/ Component.onDestruction �������/���ٲۺ���

2���� Component ���������ݲ���ֱ����ʾ����Ҫ��loader �ؼ���ʾ

3��Loader ���� source qml�ļ�������ʹ�� sourceComponent ���� Componpent

4��Loader ��ʹ�� onStatusChanged �鿴���ؿؼ���״̬�仯����asynchronous �󣬻�����loading ״̬��ֵΪ2

5��ʹ�� loader.sourceComponent = null  �����ٿؼ���source Ӧ������

6�������ط�Ҫ�޸�loader ����ؼ�ֵ����Ҫ�� loader.item. ���ܷ���

7��ͼƬ����ʹ�� 

```
////        Image {                     // ���ؾ�̬ͼ��
////            id: img
////            source: "/th.jpg"
////            width: 50               // ������С������
////            height: 50
////        }
//        AnimatedImage {               // ���ض�̬ͼ��
//            id: img
//            source: "/th2.gif"

//        }
```



## 06_qml_mouseArea

1��mouseArea �������Խ���

2����ק drag ���Խ���

3��ע�⣬����onXXX �ۺ�����Ӧ�����ж�Ӧ���Ըı�



## 07_qml_button

1��checked ���ԣ�Ĭ��false�����Ϊtrue ���ʾĬ��ѡ���������ʾ

2��checkable ��ʾ�İ�ť���Կ��Ա�ѡ��

3��checkable Ϊtrue���������� autoExclusive Ϊtrue��������ͬ����ťֻ��ѡ��1��

4��autoRepeat  Ϊtrue ����ظ���Ӧ����ʵ��

5��ʹ�� indicator ����ͼƬ��һ�㲻ʹ��

6��ʹ�� text ����ť�������֣�һ�㲻ʹ��

7������ DelayButton / RadioButton / switch / tab

8��ʹ�� ButtonGroup ������button ���Լ��ϣ����ø���Ӧ�ؼ��е�button ʹ��

9��**�Զ��尴��ʹ�� background  �����������������������ԣ�ʹ�� contentItemcontentItem ���������ػ�**



## 08_qml_property

1���������ͽ���

?		int / real / string / color / url

2��property ���Զ����������

?		property Component mycom

3����֪���Է�����ʱ����ʹ�� var 

4��list ��������

5������ǰ�� readonly ��ʾ������ֻ��

6���ⲿʹ�ñ��븳ֵ���� required

7���ⲿҪ�����ӿؼ��������� property alias ���ؼ����߿ؼ���ĳ������ȡ�����������з���

8����ʾ Invalid property name ��xxx�� M16�������ڱ�������Ϸ�����

```
// @disable-check M16
```



## 09_qml_checkbox

1��ʹ�� ButtonGroup + Column ʵ�� checkBox ����

2��Button �� ���� ButtonGroup��ʵ������

3��tristate: true             // 3̬ �� - ��



## 10_qml_text

1���������Խ���

2�������ؼ����Ȳ���ʹ��ʡ�Ժ�

3��text �ֶ�֧��html / ���ı� / ���ı�

4�����嵥���Զ�����

```
//            wrapMode: Text.WordWrap     // �Զ����ʻ���
//            anchors.fill: parent
//            elide: Text.ElideRight
```

5�������ӣ���� MouseArea ��ҳ�����



## 11_qml_popup_overlay

1����������ʹ�ã�ʹ�� contentItem �Զ��� popup

2��popup ����



## 12_qml_repeater

1��repeater ʹ��



## 13_qml_listview

1��listview ���Զ�����ͨ�������ͣ���int �������飬�͸����������ͣ���ͨ��������ʹ�� modelData ��ȡ���ԣ�

2��������������ʹ�� model: ListModel {ListElement{}} ���壬 ListElement ��ʾListModel �а�����Ԫ�أ�Ԫ���п����ж�����ԣ�ListElement Ԫ���е����ԣ�ListView �п���ֱ�ӷ���Ԫ�أ�����ʹ�� modelData��

3��ListView �У�ͨ�� delegate ʹ�� model �е��������ݣ�����ÿһ��ؼ�����

4��ͨ�� spacing ����ÿһ��ؼ����

5��highlight: Rectangle { color: "lightsteelblue"; radius: 5 }    // ����ʵ�֣�����ʵ���У�delegate: ����ʹ�� Rectangle {}

6��ListView ��ʹ��header/ footer ʵ������ⲿ���·���ӿؼ�

7��ʹ�� section + Component ʵ�ֵ�������һ�У������½ڱ���Ŀ¼

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
        
        section.property: "name"                    // ѡ�� name ����
        section.criteria: ViewSection.FullString    // ����������ʾ�����ַ������ߵ����ַ�
        section.delegate: sectionHeading            // ��Ӧÿһ�� section.property ��λ���
        boundsBehavior: Flickable.StopAtBounds      // ����Ϊ stop ���϶����ɻص�



## 14_qml_combobox

1��model �����ж��ٸ�combo box

2��editable: true                      // �ɱ༭ʹ��       �� count ���Ի�ȡ combo box ����

3���༭��������һ�� combo box������

```
//    onAccepted: {                               // �س����󴥷�
//        if (find(editText) === -1)              // ���ҵ�ǰ�ɱ༭�ı� �Ƿ��Ѵ���
//            model.append({text: editText})      // append ���һ���µ� ListElement
//    }
```

4����ȡ��ǰcombo box ����

```
//    onCurrentTextChanged: {
//        console.log(currentText)
//    }
```

5��ʹ�� validator ��������Ϸ���

6���Զ��� ComboBox ʵ�֣����� Rectangle �� ��Ӱ���� layer.effect: DropShadow



## 15_qml_focus

1��focus ��������

```
focusPolicy: Qt.NoFocus                             // ����Ϊ Qt.NoFocus ���޷���ȡ���㣬���ǻ��ǿ���ͨ�� forceActiveFocus()  ���ý���
```

2������ؼ�ͬʱ��ȡ focus �������focus ���ȡ�����㣻�ļ�����Ŀؼ����ȹ��죬�������� txt2 ���ȹ���

3��focusReason)      // ��ȡ focus ԭ��

4��//// 3��FocusScope �ؼ����ӿؼ����ܻ�ȡ�����㣬focus Ϊtrue�� FocusScope�ؼ������� focus ���ӿؼ��� focus ���ÿ����� activeFocus ҲΪ true
//// ���߼��� focus ����Ϊtrue û���⣬���Ǹ��ӿؼ�����Ҫ�� activeFocus



## 16_qml_signal

1��signal �Ͳۺ�������ʹ�ã���Ӧ3�вۺ����󶨷���

2�������첽����������¼�ͨ���Զ����źŴ���ʾ����ʹ�� Component ���ؼ� ��click �źŴ����ⲿ�ؼ��У����ⲿ�ؼ��� loader �н���



## 17_qml_c++ ��������

![image-20231005093819523](C:\Users\90952\AppData\Roaming\Typora\typora-user-images\image-20231005093819523.png)



1��c++ ��ͨ�� ����ȫ�ֱ�������qml ��ʹ��

    QQmlContext* context = engine.rootContext();
    QScreen *screen = QGuiApplication::primaryScreen();             // ��ȡ��Ļ����
    QRect rect = screen->virtualGeometry();                         // ��ȡ��Ļ���
    //context->setContextProperty("SCREEN_WIDTH", rect.width());      // SCREEN_WIDTH  Ϊȫ�ֶ���
    context->setContextProperty("SCREEN_WIDTH", 640);

2���ӿؼ���ֱ�Ӷ�������ԣ��൱�� public ���������ؼ�����ֱ�ӷ���

3���ӿؼ���ͨ�� QtObject ����ı������Լ��ڲ�����ͨ�� id. ��ʽ���ʣ��ⲿ����ͨ��ȡ������ʽ��Χ�����ַ�ʽc++ �޷�����

    QtObject {
        id: attributes                // �ⲿҪ���ʿ��Ը�����ؼ�ȡ����
        property int testValue: 0     // ���������൱�� private
    }
    
    Component.onCompleted: {
        console.log(attributes.testValue)       // ������ attributes.testValue ���ɷ��� property int testValue
    }
    
    property alias attr: attributes   // �� attributes ȡ�������ⲿ����ͨ�� attr ����(��ȡ/����)



4��ͨ�� qmlRegisterType ����ȫ�����qml ��ʹ��

    // ע�ᵱǰ���ͣ���QML �оͿ��Է��ʣ�"MyObj" ��Ҫ����������ƣ������ǰ汾�ţ�����ǿؼ���
    qmlRegisterType<MyObect>("MyObj", 1, 0, "MyObect"); //����һ��Ҫͨ����������������һ�������Զ����object

���У��󶨲���������qml �У�Ҳ������c++ �У��źſ��Զ�����qml ��Ҳ���Զ�����c++��



## 18_qml_cpp_qmlRegisterSingletonType

1��ʹ�� qmlRegisterSingletonType ʵ��ȫ�ֵ�������

    // ȫ�ֵ������ӣ�ʵ�ֺ� qml ���п���ֱ������������
    // �����ĺô��ǲ�����qml ������obj
    qmlRegisterSingletonType<MyObject>("MyObj", 1, 0, "MyObject", MyObject::getInstance);

���У��󶨲���������qml �У�Ҳ������c++ �У��źſ��Զ�����qml ��Ҳ���Զ�����c++��



## 19_qml_cpp

1��ʹ�� QMetaObject::invokeMethod ��c++ �˵���qml �еĺ���



## 20_qml_qmlRegisterUncreatableMetaObject

1��ʹ�� qmlRegisterUncreatableMetaObject ����������ᱨ����ʾ�����һ������

    // ע��һ�����ͣ�qml �в��ܴ���ʵ����ֻ�ܷ��ʵ������������ö��
    qmlRegisterUncreatableMetaObject(MyObject::staticMetaObject, "MyObj", 1, 0, "MyObject", "Access to enums & flags only");



## 21_qml_layout

1��Column / Row / Flow ʹ��

2�������ť�����������Զ� Column ����

3�����ֶ��� move / add / populate



## 22_qml_grid_opacitymask

1��Grid �� OpacityMask ���ʹ�ã�OpacityMask ���Խ�2��ͼ��ϲ�

2��anchors.fill: parent ����ô��ʾ���ؼ������ô�̶�һ��

    Rectangle {
        width: grid.width + 4
        height: grid.height +4      // �������� 4 pixel
        border.color: "red"
        border.width: 3
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter       // ͨ����2�п��Թ̶�һ��λ�ã���������߶ȣ��ײ�Ҳ�����
        anchors.bottom: parent.bottom
    
        OpacityMask {               // �ӿؼ��Ḳ�Ǹ��ؼ�
            source: grid            // �ϲ�Դ
            maskSource: maskRect    // �ڸ�Դ
            anchors.fill: parent
            anchors.margins: 2      // ��������2 pixel
        }
    }

3����ô��С Repeater ���ƿ���



## 23_qml_find_subobject

1��ʹ�� itemAt() ������Repeater ��model��  ���������

2��ͨ�� col.children.length ��ȡ Column������Ŀ����

3��ͨ��  contentItem ��ȡ ListView ������



## 24_qml_timer

qml timer ʹ��



## 24_qml_user_model

1���½� qt item model -> QAbstractListModel �����Զ���c++ ��

2��c++ ������ö�٣�key����ͨ�� rowCount ����qml model �м���Ԫ�أ�ͨ�� roleNames ����c++ ��qml ӳ�䣬 �ַ�����ö�ٵ�ӳ�䣬ö��c++���弴key���ַ�����qml��ʹ�ã� ���ͨ�� data ���� key ��Ӧ�������ݷ��صľ���ʵ�֡�



## 25_qml_user_model

���ṹ��



## 26_qml_listview2

1��SwipeView ����

2���Զ��� SwipeView Ч����ʹ�� ObjectModel �Զ���������ݸ� ListView

3��ʹ�� XmlListModel ����ȡ xml �����ݣ����ݸ� ListView



## 27_qml_qdatastream

����



## 28_qml_cpp_QString

1��ʹ�� QList<QString> ����һ��list ���飻ʹ�� QListIterator<QString> iter(list) ����ȡ������

2��ʹ�� list.join

3��split �ָfor ѭ��

4��// ���ļ� QFile file(":/test.txt");



## 29_qml_textedit

�� TextEdit �� text ȡ�����������ⲿ������

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
    // ͨ�������������� �����ƶ�����
    Keys.onLeftPressed: square.x -= 8
    Keys.onRightPressed: square.x += 8
    Keys.onUpPressed: square.y -= 8
    Keys.onDownPressed: square.y += 8

    Keys.onPressed: {
        switch(event.key) {             // �Ӽ��Ŵ���С����
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

���� singleton  �����ж�����һ���ļ��У��Ӷ������е�ģ����ʹ�á�

�����ķ���ͬ���ʺ�����style���ǵ�Ӧ�á�������һ���ط��޸����ã����������е�ģ���ж�ʹ�á�

��������C/C++�ж���һЩ�������ڲ�ͬ��.cpp�ļ���ʹ��һ����

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

���ȣ����ǿ��Կ����������ļ��Ŀ�ʼ����ʹ����pragam Singleton����������ļ���ʵ����ʱֻ����һ��ʵ����

���⣬���Ǳ���������Ӧ�õĸ�Ŀ¼��������µ� **qmldir** �ļ���

```
singleton Settings 1.0 Settings.qml
```

�ο��� [QML Styling �� Singleton ʹ�÷���ǳ̸_qml singleton-CSDN����](https://blog.csdn.net/ubuntutouch/article/details/46980635)



## 32_qml_flickable

ʹ�� Flickable ��ʵ�� page ���ܣ��������»�����



## 33_qml_createObject

1��ʹ�� Component.createObject  ����̬����

2������һ��������ά�����ٶ�̬���������



```
   property var itemCells: new Array  
   Component.onCompleted: {
   	   var cellCount = itemCells.length
       for(var i = 0;i < cellCount;i++){
          itemCells.pop().destroy();
       }

	itemCells.push(com.createObject(root,{width: 300}))     // ��̬��������ͨ�� itemCells ��������

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



�ο��� [05��̬����QML����_qml createobject-CSDN����](https://blog.csdn.net/u013064585/article/details/108350797)









