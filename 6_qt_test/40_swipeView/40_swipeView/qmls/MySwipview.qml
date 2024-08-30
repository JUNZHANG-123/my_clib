import QtQuick 2.0
//import QtMultimedia 5.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import "../../Funcs/UILogics.js" as UILogic
import "../../Style"
import "../../Components"
import "../../Global"
import DevStateMonitor.DevStateDefine 1.0
import com.zyb.PingDefine 1.0
import QtGraphicalEffects 1.0

ZybRectangle {
    id : listen_root
    color: "#FFE8FAD1"
    hasTitle: false

    signal sig_back()

    property var pageType: "englishlisten"
    property var nodeArray: new Array
    property string requestGradeName : ""
    property int loadFailed_resState : 1  //1 最近  2同步词书 3情景例句 4必备词书
    property int img_load_check : 0	  //用于检测book img 是否都加载成功
    property var isNeedPreinit : true
    property var isNeedPreUpdateSceneVideo : false
    property var oldPlayerLoaderId : playerLoader
    property var playerLoaderId : playerLoader
    property var oldPlayerMode : 0    // 记录上一个播放界面，用于判断后台播放是否需要切换播放器
    property var oldPlayerPid : 0     // 记录上一个播放界面，用于判断后台播放是否需要切换播放器

    onHotkeyBack: {
        sig_back()
    }

    function setArgs(param)
    {

    }

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
                    updateHistory();
                }
            }
        },
        State {
            name: "history_no"
            StateChangeScript {
                script: {
                    console.log("history_no state")
                }
            }
        },
        State {
            name: "syn_word"
            StateChangeScript {
                script: {
                    console.log("syn_word state")
                    updateSynWord();
                }
            }
        },

        State {
            name: "scene_example"
            StateChangeScript {
                script: {
                    console.log("scene_example state")
                    updateSceneExample();
                }
            }
        },

        State {
            name: "must_recite"
            StateChangeScript {
                script: {
                    console.log("must_recite state")
                    updateMustRecite();
                }
            }
        },

        State {
            name: "listen_examination"
            StateChangeScript {
                script: {
                    console.log("listen_examination state")
                    updateListenExamination();
                }
            }
        },

        State {
            name: "load_falied"
            StateChangeScript {
                script: {
                    console.log("load_falied state")
                    mainSwipeView.itemAt(menuList.currentIndex).parentSta = "load_falied"
                }
            }
        },
        State {
            name: "net_error"
            StateChangeScript {
                script: {
                    console.log("net_error state")
                    mainSwipeView.itemAt(menuList.currentIndex).parentSta = "net_error"
                }
            }
        }
    ]

    PageBackButton{
        id:backButton
        iconSource: "qrc:/images/ZB02/englishlisten/el_back.png"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 22+34
        anchors.leftMargin: 40
        onBackClicked: {
            sig_back()
        }
    }

    Item {
        id: gradeCombox
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 34
        width: 289+79
        height: 100
        visible: listen_root.state === "syn_word"
        z: 1

        Image {
            id: gardMaskIcon
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/images/ZB02/englishlisten/el_grade_mask.png"
        }

        Rectangle {
            anchors.right: parent.right
            width: 289
            height: 100
            color: listen_root.color

            Rectangle {
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                width: 169
                height: 64
                color: Qt.rgba(0,0,0,0.06)
                radius: 32

                ZybText {
                    id: gradeName
                    font.styleName: "Regular"
                    font.pixelSize: Style2.pixelSize3
                    color: Qt.rgba(0,0,0,0.8)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: triangleIcon.left
                    anchors.rightMargin: 8
                    text:requestGradeName
                }

                Image {
                    id:triangleIcon
                    anchors.right: parent.right
                    anchors.rightMargin: 27
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: -1
                    source: "qrc:/images/ZB02/englishlisten/el_combox.png"
                }

                MouseArea{
                    anchors.fill: parent
                    anchors.margins: -20

                    onClicked: {

                        console.log("gradeName- clicked");
                        //globalUI.showLoading2ClickHide("加载中");
                        showDarkBackground();
                        openGradePage();
                    }
                }
            }
        }
    }

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
        ListElement {
            name: "必备词书"
        }
        ListElement {
            name: "中高考听力"
        }
    }

    ListView{
        id:menuList
        anchors.top: parent.top
        anchors.topMargin: 34
        anchors.left: parent.left
        anchors.leftMargin: 56+40
        anchors.right: parent.right
        height: 100
        orientation: ListView.Horizontal
        model: topModel
        Component {
            id : unitDelegate
            Rectangle {
                id: uint
                width: content_text.paintedWidth+52
                height: parent.height
                color: listen_root.color
                opacity: uint.ListView.isCurrentItem? 0.8: 0.6

                ZybText{
                    id:content_text
                    text: name
                    color: "#FF000000"
                    width: parent.width
                    font.styleName: uint.ListView.isCurrentItem? "Medium" : "Regular"
                    font.pixelSize: uint.ListView.isCurrentItem? Style2.pixelSize6 : Style2.pixelSize4
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
                        mainSwipeView.contentItem.highlightMoveDuration = 0
                        mainSwipeView.setCurrentIndex(index);

                        enListenManager.setLastTabIndex(index);
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
                        case 3:
                            listen_root.state = "must_recite"
                            break
                        case 4:
                            listen_root.state = "listen_examination"
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
            case 3:
                listen_root.state = "must_recite"
                break
            case 4:
                listen_root.state = "listen_examination"
                break
            }
        }

        delegate: unitDelegate
        clip: true
    }

    Component {
        id:dynamicPageComponent

        EnAlbumRect {
            visible: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem

            onSigUpdatePage: {
                console.log("onSigUpdatePage")
                updatePage();
            }

            onSigReload: {
                switch(curIndex)
                {
                case 0:
                    parentSta = "history";
                    break
                case 1:
                    parentSta = "syn_word";
                    break
                case 2:
                    parentSta = "scene_example";
                    break
                case 3:
                    parentSta = "must_recite";
                    break
                case 4:
                    parentSta = "listen_examination"
                    break
                }
            }
        }
    }

    SwipeView
    {
        id: mainSwipeView
        anchors.top: parent.top
        anchors.topMargin: 154
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

    Rectangle {
        id: darkBackground
        anchors.fill: parent
        color: "#99000000"
        visible: opacity !== 0
        z: 2
        opacity: 0

        Behavior on opacity {
            NumberAnimation { duration: 300; easing.type: Easing.OutCubic }
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
    }

    function showDarkBackground() {
        darkBackground.opacity = 1;
    }

    function hideDarkBackground() {
        darkBackground.opacity = 0;
    }

    Loader {
        id:gradeLoader
        anchors.centerIn: parent
        active: false
        source: "qrc:/qmls/Pages/EnglishListen/EnGradePage.qml"
        z: 3
        onLoaded:
        {
            console.log("playerLoader loaded");

        }
    }

    function openGradePage()
    {
        if (!gradeLoader.active)
        {
            gradeLoader.active = true;
            gradeLoader.item.accepted.connect(function(strName){
                console.log("loaderGradeSelect accepted",strName);
                gradeLoader.active = false
                hideDarkBackground();
                if(gradeName.text !== strName)
                {
                    if(netChannelManager.getNetState() === false)
                    {
                        switch_state_timer.start();
                        return;
                    }

                    requestGradeName = strName;
                    mainSwipeView.currentItem.clearData();
                    globalUI.showLoading2ClickHide("请求中");
                    enListenManager.setGrade(strName);
                    enListenManager.clearSynBookList();
                    apiNetWork.sendApiGetEnglistProductList(1,enListenManager.getGrade());
                    gradeName.text = strName;
                }
            });

            gradeLoader.item.rejected.connect(function(){
                console.log("loaderGradeSelect rejected");
                gradeLoader.active = false
                hideDarkBackground();
            });

            gradeLoader.item.curGradeName = gradeName.text
            gradeLoader.item.open();
        }
    }

    Item {
        id: littlePlayer
        anchors.left: parent.left
        anchors.leftMargin: 28
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 28
        width: 89+83
        height: 88
        visible: playerLoader.visible === false? true: player2Loader.visible === false? true: false

        Image {
            id: littlePlayerBg
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/images/ZB02/englishlisten/el_little_player_bg.png"
            z: 1

            CircularImage
            {
                id: cover_img
                anchors.fill: parent
                anchors.margins: 18
                radius: 50
            }

            RotationAnimation {
                id: rotationAnimation
                target: cover_img
                from: 0
                to: 360
                duration: 5000 // 旋转一周所需的时间（毫秒）
                loops: Animation.Infinite // 无限循环
            }

            MouseArea {
                anchors.fill: parent
                anchors.margins: -20
                onClicked:
                {
                    playerLoaderId.visible = true
                }
            }
        }

        Item {
            width: 121
            height: 75
            anchors.left: parent.left
            anchors.leftMargin: 51
            anchors.verticalCenter: parent.verticalCenter

            Item {
                id: blurItem
                visible: false
                anchors.fill: parent

                Image {
                    id: backgroundImage
                    asynchronous:true
                    cache: false
                    visible: false
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                    source: cover_img.img_src
                    sourceSize: Qt.size(parent.width, parent.height)
                    antialiasing: true
                }

                GaussianBlur {
                    anchors.fill: parent
                    source: backgroundImage
                    radius: 10
                }
            }

            Image {
                id: maskImage
                anchors.fill: parent
                source: "qrc:/images/ZB02/englishlisten/el_little_player_mask.png"
            }

            OpacityMask {
                anchors.fill: blurItem
                source: blurItem
                maskSource: maskImage
                visible: true
            }
        }

        Image {
            id: littlePlayIcon
            anchors.left: littlePlayerBg.right
            anchors.leftMargin: 14
            anchors.verticalCenter: littlePlayerBg.verticalCenter
            source: "qrc:/images/ZB02/englishlisten/el_little_pause.png"
            z: littlePlayerBg.z

            MouseArea
            {
                anchors.fill: parent
                anchors.margins: -20
                onClicked:
                {
                    if (playerManager.getPlayState())
                    {
                        playerManager.pause()
                    }
                    else
                    {
                        playerManager.play()
                    }
                }
            }
        }
    }

    // Button {
    //     id: test_up
    //     width: 100
    //     height: 100
    //     visible: true
    //     anchors.left: littlePlayer.right
    //     anchors.leftMargin: 20
    //     anchors.verticalCenter: littlePlayer.verticalCenter
    //     text: "上一曲"

    //     onClicked: {
    //         console.error("previousPlay")
    //         playerManager.previousPlay()
    //     }
    // }

    // Button {
    //     id: test_down
    //     width: 100
    //     height: 100
    //     visible: true
    //     anchors.left: test_up.right
    //     anchors.leftMargin: 20
    //     anchors.verticalCenter: test_up.verticalCenter
    //     text: "下一曲"

    //     onClicked: {
    //         console.error("nextPlay")
    //         playerManager.nextPlay()
    //     }
    // }

    Loader {
        id:playerLoader
        anchors.fill: parent
        active: false
        source: "qrc:/qmls/Pages/EnglishListen/EnPlayer.qml"
        z:100
        onLoaded:
        {
            console.log("playerLoader loaded");

        }
    }

    Loader {
        id:player2Loader
        anchors.fill: parent
        active: false
        source: "qrc:/qmls/Pages/EnglishListen/EnPlayer2.qml"
        z:100
        onLoaded:
        {
            console.log("player2Loader loaded");

        }
    }

    function openPlayerPage(mode,pId,pindex)
    {
        console.warn("openPlayerPage:", mode,pId,pindex, listen_root.state);

        if (oldPlayerMode !== mode || oldPlayerPid !== pId)
        {
            playerLoaderId.active = false
        }

        if (mode === GlobalProperty.listenExaminationModuleId)
        {
            playerLoaderId = player2Loader
        }
        else 
        {
            playerLoaderId = playerLoader
        }

        playerLoaderId.visible = true;
        if (!playerLoaderId.active)
        {
            img_check_timer.stop()

            showPulseLoader(pId)

            playerLoaderId.active = true;
            playerLoaderId.item.sigBack.connect(function(mod, proId) {
                console.log("playerPage sigBack",mod,proId);
                playerLoaderId.visible = false;
                rotationAnimation.start()
                updateGridItemProgress(mod,proId)
            });

            playerLoaderId.item.sigAlbumPlayStaChange.connect(function(proId, isPlaying) {
                console.log("sigAlbumPlayStaChange: isPlaying", isPlaying, "proId", proId);
                if (isPlaying) {
                    changePulseLoaderAnimSta(proId, true)
                    playerManager.setPlayState(1)
                } else {
                    changePulseLoaderAnimSta(proId, false)
                    playerManager.setPlayState(0)
                }
            });

            playerLoaderId.item.sigPlayNext.connect(
                function(prodId, progess){
                    console.log("sigExit: update history")

                    var isFound = false
                    for (var i = 0; i < mainSwipeView.itemAt(0).getListModelCount(); i++) {
                        if (mainSwipeView.itemAt(0).getListModel().get(0).m_productId === prodId) {
                            isFound = true

                            if (progess > mainSwipeView.itemAt(0).getListModel().get(0).m_progress) {
                                mainSwipeView.itemAt(0).setListModelProperty(i , "m_progress", progess)
                            }
                            break
                        }
                    }

                    var jsonArray = enListenManager.getHistoryBookListData()
                    if(jsonArray.length > 0)
                    {
                        if (!isFound)
                        {
                            globalUI.showLoading2ClickHide("请求中");
                            mainSwipeView.itemAt(0).clearData();
                            for(var i = 0; i < jsonArray.length; i++)
                            {
                                var tmpItem = {};
                                var gitem = jsonArray[i];
                                tmpItem["m_controlData"]   = gitem;
                                tmpItem["m_index"]         = gitem["curInex"];
                                tmpItem["m_source"]        = gitem["picture"].length===0?"qrc:/images/listen_book_default.png":gitem["picture"];
                                tmpItem["m_title"]         = gitem["name"];
                                tmpItem["m_productId"]     = gitem["id"];
                                tmpItem["m_resourceCount"] = gitem["resourceCount"];
                                tmpItem["m_progress"]      = gitem["progress"];
                                tmpItem["m_moduleId"]      = gitem["moduleId"];
                                if (i === 0)
                                {
                                    tmpItem["m_pulseLoaderRunAnim"]      = true
                                    tmpItem["m_pulseLoaderVisible"]      = true
                                }
                                else
                                {
                                    tmpItem["m_pulseLoaderRunAnim"]      = false
                                    tmpItem["m_pulseLoaderVisible"]      = false
                                }

                                mainSwipeView.itemAt(0).setData(tmpItem)
                            }
                            globalUI.hideLoading2();
                        }

                        for(var i = 0; i < jsonArray.length; i++)
                        {
                            var gitem = jsonArray[i];
                            var m_cover = gitem["picture"].length===0?"qrc:/images/listen_book_default.png":gitem["picture"];
                            var m_pid   = gitem["id"];

                            if (m_pid === prodId)
                            {
                                playerManager.setCover(m_cover);
                                break;
                            }
                        }
                    }
                }
            );

            console.log("openPlayerPage",mode,pId,pindex)

            var resSize = enListenManager.getPlaylistByModule(mode).length;
            if(pindex === resSize)
            {
                playerLoaderId.item.curIndex = 0
            }
            else
            {
                playerLoaderId.item.curIndex = pindex
            }
            playerLoaderId.item.productId = pId
            playerLoaderId.item.maxIndex = enListenManager.getBookMaxIndex(mode, pId);
            playerLoaderId.item.mode = mode
        }
        oldPlayerPid = pId
        oldPlayerMode = mode
    }

    function showPulseLoader(pId)
    {
        for (var j = 0; j < 5; j++) {
            for (var i = 0; i < mainSwipeView.itemAt(j).getListModelCount(); i++)
            {
                if (mainSwipeView.itemAt(j).getListModel().get(i).m_productId === pId) {
                    mainSwipeView.itemAt(j).setListModelProperty(i , "m_pulseLoaderRunAnim", true)
                    mainSwipeView.itemAt(j).setListModelProperty(i , "m_pulseLoaderVisible", true)
                    break;
                }
            }
        }

        if ( oldPlayerPid !== pId) {
            for (var j = 0; j < 5; j++) {
                for (var i = 0; i < mainSwipeView.itemAt(j).getListModelCount(); i++)
                {
                    if (mainSwipeView.itemAt(j).getListModel().get(i).m_productId === oldPlayerPid) {
                        mainSwipeView.itemAt(j).setListModelProperty(i , "m_pulseLoaderRunAnim", false)
                        mainSwipeView.itemAt(j).setListModelProperty(i , "m_pulseLoaderVisible", false)
                        break;
                    }
                }
            }
        }
    }

    function changePulseLoaderAnimSta(pId, sta)
    {
        for (var j = 0; j < 5; j++) {
            for (var i = 0; i < mainSwipeView.itemAt(j).getListModelCount(); i++)
            {
                if (mainSwipeView.itemAt(j).getListModel().get(i).m_productId === pId) {
                    mainSwipeView.itemAt(j).setListModelProperty(i , "m_pulseLoaderRunAnim", sta)
                    mainSwipeView.itemAt(j).setListModelProperty(i , "m_pulseLoaderVisible", true)
                    break;
                }
            }
        }
    }

    Timer
    {
        id:clearTimer
        interval: 1
        repeat: false
        onTriggered:
        {
            switch(menuList.currentIndex)
            {
            case 0:
                updateGridContentByHistory();
                break
            case 1:
                updateGridContentBySynWord();
                break
            case 2:
                updateGridContentBySceneExample();
                break
            case 3:
                updateGridContentByMustRecite();
                break
            case 4:
                updateGridContentByListenExamination();
                break
            }
        }
    }

    Timer
    {
        id: img_check_timer
        interval: 10000
        repeat: false
        onTriggered:
        {
            if(netChannelManager.getNetState())
            {
                listen_root.state = "load_falied"
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
                case 3:
                    listen_root.state = "must_recite"
                    break
                case 4:
                    listen_root.state = "listen_examination"
                    break
                }
            }
            else
            {
                switch_state_timer.start();
            }
        }
    }

    Timer
    {
        id:history_switch_to_historyNo_state
        interval: 1
        onTriggered:
        {
            listen_root.state = "history_no"
        }
    }

    function clearGrid()
    {
        for (var i = 0; i < mainSwipeView.count; i++) {
            mainSwipeView.itemAt(i).clearData();
            mainSwipeView.itemAt(i).parentSta = "none"
        }
    }

    function updatePage()
    {
        console.log("updatePage")
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
        case 3:
            listen_root.state = "must_recite"
            break
        case 4:
            listen_root.state = "listen_examination"
            break
        }
    }

    function updateGridItemProgress(pmodule,pProcId)
    {
        var curState = listen_root.state;

        if(curState === "history")
        {
            updateGridContentByHistory();
        }
        else if(curState === "syn_word")
        {
            updateGridContentBySynWord();
        }
        else if(curState === "scene_example")
        {
            updateGridContentBySceneExample();
        }
        else if(curState === "must_recite")
        {
            updateGridContentByMustRecite();
        }
        else if(curState === "listen_examination")
        {
            updateGridContentByListenExamination();
        }
    }

    function updateGridContentByHistory()
    {
        if (mainSwipeView.count === 0) {
            for (var i = 0; i < 5; i++) {
                var item = dynamicPageComponent.createObject(mainSwipeView, {})
                mainSwipeView.addItem(item)
            }
        }

        // 播放器退出时会更新
        if (mainSwipeView.currentItem.getListModelCount() > 0) {
            console.log("mainSwipeView.currentIndex=", mainSwipeView.currentIndex, "context=",
                        mainSwipeView.currentItem.getListModelCount(), "already create")

            mainSwipeView.itemAt(menuList.currentIndex).parentSta = listen_root.state
            return;
        }

        var jsonArray = enListenManager.getHistoryBookListData()
        console.log("updateGridContentByHistory size =",jsonArray.length)
        if(jsonArray.length > 0)
        {
            mainSwipeView.currentItem.clearData();
            mainSwipeView.currentItem.parentSta = "history"

            img_load_check = 0;
            for(var i = 0; i < jsonArray.length; i++){
                var tmpItem = {};
                var gitem = jsonArray[i];
                tmpItem["m_controlData"]   = gitem;
                tmpItem["m_index"]         = gitem["curInex"];
                tmpItem["m_source"]        = gitem["picture"].length===0?"qrc:/images/listen_book_default.png":gitem["picture"];
                tmpItem["m_title"]         = gitem["name"];
                tmpItem["m_productId"]     = gitem["id"];
                tmpItem["m_resourceCount"] = gitem["resourceCount"];
                tmpItem["m_progress"]      = gitem["progress"];
                tmpItem["m_moduleId"]      = gitem["moduleId"];
                tmpItem["m_pulseLoaderRunAnim"]      = false
                tmpItem["m_pulseLoaderVisible"]      = false
                mainSwipeView.currentItem.setData(tmpItem)

                img_load_check++;
            }
        }
        else
        {
            history_switch_to_historyNo_state.restart();
            //listen_root.state = "history_no" //QML StateGroup: Can't apply a state change as part of a state definition.
        }
    }

    function updateGridContentBySynWord()
    {
        if (mainSwipeView.currentItem.getListModelCount() > 0) {
            console.log("mainSwipeView.currentIndex=", mainSwipeView.currentIndex, "context=",
                        mainSwipeView.currentItem.getListModelCount(), "already create")

            mainSwipeView.itemAt(menuList.currentIndex).parentSta = listen_root.state
            return;
        }

        var jsonArray = enListenManager.getSynBookListData()
        console.log("updateGridContentBySynWord size =",jsonArray.length)

        mainSwipeView.currentItem.clearData();
        mainSwipeView.currentItem.parentSta = "syn_word"

        img_load_check = 0;
        for(var i = 0;i < jsonArray.length;i++){
            var tmpItem = {};
            var gitem = jsonArray[i];
            tmpItem["m_controlData"]   = gitem;
            tmpItem["m_index"]         = gitem["curInex"] === undefined? 0: gitem["curInex"];
            tmpItem["m_source"]        = gitem["picture"].length===0?"qrc:/images/listen_book_default.png":gitem["picture"];
            tmpItem["m_title"]         = gitem["name"];
            tmpItem["m_productId"]     = gitem["id"];
            tmpItem["m_resourceCount"] = gitem["resourceCount"];
            tmpItem["m_progress"]      = gitem["progress"];
            tmpItem["m_moduleId"]      = gitem["moduleId"];
            tmpItem["m_pulseLoaderRunAnim"]      = false
            tmpItem["m_pulseLoaderVisible"]      = false

            if (gitem["name"] === "高中高频词组" || gitem["name"] === "高中高频词")
            {
                continue;
            }

            mainSwipeView.currentItem.setData(tmpItem)
            img_load_check++;
        }

        console.error("mainSwipeView.currentItem.getListModelCount", mainSwipeView.currentItem.getListModelCount(1))
    }

    function updateGridContentBySceneExample()
    {
        if (mainSwipeView.currentItem.getListModelCount() > 0) {
            console.log("mainSwipeView.currentIndex=", mainSwipeView.currentIndex, "context=",
                        mainSwipeView.currentItem.getListModelCount(), "already create")

            mainSwipeView.itemAt(menuList.currentIndex).parentSta = listen_root.state
            return;
        }

        var jsonArray = enListenManager.getSceneExampleBookListData()
        console.log("updateGridContentBySceneExample size =",jsonArray.length)

        mainSwipeView.currentItem.clearData();
        mainSwipeView.currentItem.parentSta = "scene_example"

        img_load_check = 0;
        for(var i = 0;i < jsonArray.length;i++){
            var tmpItem = {};
            var gitem = jsonArray[i];
            tmpItem["m_controlData"]   = gitem;
            tmpItem["m_index"]         = gitem["curInex"];
            tmpItem["m_source"]        = gitem["picture"].length===0?"qrc:/images/listen_book_default.png":gitem["picture"];
            tmpItem["m_title"]         = gitem["name"];
            tmpItem["m_productId"]     = gitem["id"];
            tmpItem["m_resourceCount"] = gitem["resourceCount"];
            tmpItem["m_progress"]      = gitem["progress"];
            tmpItem["m_moduleId"]      = gitem["moduleId"];
            tmpItem["m_pulseLoaderRunAnim"]      = false
            tmpItem["m_pulseLoaderVisible"]      = false
            mainSwipeView.currentItem.setData(tmpItem)
            img_load_check++;
        }
    }

    function updateGridContentByMustRecite()
    {
        if (mainSwipeView.currentItem.getListModelCount() > 0) {
            console.log("mainSwipeView.currentIndex=", mainSwipeView.currentIndex, "context=",
                        mainSwipeView.currentItem.getListModelCount(), "already create")

            mainSwipeView.itemAt(menuList.currentIndex).parentSta = listen_root.state
            return;
        }

        var jsonArray = enListenManager.getMustReciteBookListData()
        console.log("updateGridContentByMustRecite size =",jsonArray.length)

        mainSwipeView.currentItem.clearData();
        mainSwipeView.currentItem.parentSta = "must_recite"

        img_load_check = 0;
        for(var i = 0;i < jsonArray.length;i++){
            var tmpItem = {};
            var gitem = jsonArray[i];
            tmpItem["m_controlData"]   = gitem;
            tmpItem["m_index"]         = gitem["curInex"];
            tmpItem["m_source"]        = gitem["picture"].length===0?"qrc:/images/listen_book_default.png":gitem["picture"];
            tmpItem["m_title"]         = gitem["name"];
            tmpItem["m_productId"]     = gitem["id"];
            tmpItem["m_resourceCount"] = gitem["resourceCount"];
            tmpItem["m_progress"]      = gitem["progress"];
            tmpItem["m_moduleId"]      = gitem["moduleId"];
            tmpItem["m_pulseLoaderRunAnim"]      = false
            tmpItem["m_pulseLoaderVisible"]      = false
            mainSwipeView.currentItem.setData(tmpItem)

            img_load_check++;
        }
    }

    function updateGridContentByListenExamination()
    {
        if (mainSwipeView.currentItem.getListModelCount() > 0) {
            console.log("mainSwipeView.currentIndex=", mainSwipeView.currentIndex, "context=",
                        mainSwipeView.currentItem.getListModelCount(), "already create")

            mainSwipeView.itemAt(menuList.currentIndex).parentSta = listen_root.state
            return;
        }

        var jsonArray = enListenManager.getListenExaminationBookListData()
        console.log("updateGridContentByListenExamination size =",jsonArray.length)

        mainSwipeView.currentItem.clearData();
        mainSwipeView.currentItem.parentSta = "listen_examination"

        img_load_check = 0;
        for(var i = 0;i < jsonArray.length;i++){
            var tmpItem = {};
            var gitem = jsonArray[i];
            tmpItem["m_controlData"]   = gitem;
            tmpItem["m_index"]         = gitem["curInex"];
            tmpItem["m_source"]        = gitem["picture"].length===0?"qrc:/images/listen_book_default.png":gitem["picture"];
            tmpItem["m_title"]         = gitem["name"];
            tmpItem["m_productId"]     = gitem["id"];
            tmpItem["m_resourceCount"] = gitem["resourceCount"];
            tmpItem["m_progress"]      = gitem["progress"];
            tmpItem["m_moduleId"]      = gitem["moduleId"];
            tmpItem["m_pulseLoaderRunAnim"]      = false
            tmpItem["m_pulseLoaderVisible"]      = false
            mainSwipeView.currentItem.setData(tmpItem)

            img_load_check++;
        }
    }

    Connections {
        target: netChannelManager
        function onNetStateChanged(sta)
        {
            console.warn("onNetStateChanged",sta,listen_root.state)
            if(sta)
            {
               if(listen_root.state === "net_error")
                   updatePage();
            }
        }
    }

    Connections {
        target: enListenManager;
        function onSigSceneExampleBookDataGeted()
        {
            if(menuList.currentIndex === 2)
            {
                listen_root.state = "scene_example"
                updateGridContentBySceneExample();
                globalUI.hideLoading2();
            }
        }

        function onSigSynBookDataGeted()
        {
            if(menuList.currentIndex === 1)
            {
                listen_root.state = "syn_word"
                updateGridContentBySynWord();
                globalUI.hideLoading2();
            }
        }

        function onSigMustReciteBookDataGeted()
        {
            if(menuList.currentIndex === 3)
            {
                listen_root.state = "must_recite"
                updateGridContentByMustRecite();
                globalUI.hideLoading2();
            }
        }

        function onSigListenExaminationDataGeted()
        {
            if(menuList.currentIndex === 4)
            {
                listen_root.state = "listen_examination"
                updateGridContentByListenExamination();
                globalUI.hideLoading2();
            }
        }

        function onSigWordDataGeted(moduleId, productId, curPlayerIndex)
        {
            openPlayerPage(moduleId,productId,curPlayerIndex);
            globalUI.hideLoading2();
        }

        function onSigAudioDataGeted(moduleId, productId, curPlayerIndex)
        {
            if (moduleId === GlobalProperty.listenExaminationModuleId)
            {
                //请求 enSubtitle 中的srt 字幕内容
                if (curPlayerIndex >= enListenManager.getSceneExampleDataResoureCount())
                {
                    curPlayerIndex = 0;
                }
                var arry  = enListenManager.getPlaylistByModule(moduleId);
                var gitem = arry[curPlayerIndex];

                apiNetWork.sendApiGetListenExaminationSrt(gitem["enSubtitle"], false);   
            }
            else
            {
                openPlayerPage(moduleId,productId,curPlayerIndex);
            }

            globalUI.hideLoading2();
        }

        function onSigParseSrtDone(moduleId, productId, curPlayerIndex)
        {
            openPlayerPage(moduleId,productId,curPlayerIndex);
            globalUI.hideLoading2();
        }

        function onSigHistoryDataGeted()
        {
            console.log("onSigHistoryDataGeted",listen_root.state)

            if (isNeedPreinit)
            {
                isNeedPreinit = false
                init()
                globalUI.hideLoading2();
            }
            else 
            {
                if(menuList.currentIndex === 0)
                {
                    listen_root.state = "history"
                    console.log("onSigHistoryDataGeted,updateGridContentByHistory")
                    updateGridContentByHistory();
                    globalUI.hideLoading2();
                }
            }
        }

        function onSigUpdateEnBookItemPage()
        {
            updateGridItemProgress(0, 0);
        }
    }

    Connections{
        target: playerManager

        function onSigCoverChanged(url)
        {
            cover_img.img_src = url;
        }

        function onSigPlayerStaChanged(sta)
        {
            if (sta)
            {
                littlePlayIcon.source = "qrc:/images/ZB02/englishlisten/el_little_pause.png"
                if (rotationAnimation.running)
                {
                    rotationAnimation.resume()
                }
                else
                {
                    rotationAnimation.start()
                }
            }
            else
            {
                littlePlayIcon.source = "qrc:/images/ZB02/englishlisten/el_little_play.png"
                if (rotationAnimation.running)
                {
                    rotationAnimation.pause()
                }
                else
                {
                    rotationAnimation.stop()
                }
            }
        }

        function onSigPlayError(reason)
        {
            UILogic.showTip(reason)
        }
    }

    Connections
    {
        target:apiNetWork
        function onSig_getEnglistProductDetailTimeout(productId)
        {
            globalUI.hideLoading2();
            globalUI.showBottomSnackbar(true,qsTr("网络请求超时，请重试"),Style.pixelSize24,qsTr(""),"")
        }

        function onSig_getEnglistProductListTimeout(moduleId)
        {
            globalUI.hideLoading2();
            if(moduleId === 1)
            {
                if(listen_root.state === "syn_word")
                {
                    globalUI.hideLoading2();
                    globalUI.showBottomSnackbar(true,qsTr("网络请求超时，请重试"),Style.pixelSize24,qsTr(""),"")
                    listen_root.state = "load_falied";
                    loadFailed_resState = 2;
                }
            }
            else if(moduleId === 3)
            {
                if(listen_root.state === "scene_example")
                {
                    globalUI.hideLoading2();
                    globalUI.showBottomSnackbar(true,qsTr("网络请求超时，请重试"),Style.pixelSize24,qsTr(""),"")
                    listen_root.state = "load_falied";
                    loadFailed_resState = 3;
                }
            }
            else if(moduleId === GlobalProperty.listenExaminationModuleId)
            {
                if(listen_root.state === "listen_examination")
                {
                    globalUI.hideLoading2();
                    globalUI.showBottomSnackbar(true,qsTr("网络请求超时，请重试"),Style.pixelSize24,qsTr(""),"")
                    listen_root.state = "load_falied";
                    loadFailed_resState = 5;
                }
            }

        }

        function onSig_getEnglishRecordTimeout()
        {

            if(listen_root.state === "history")
            {
                globalUI.hideLoading2();
                listen_root.state = "load_falied";
                loadFailed_resState = 1;
            }
        }

        function onSig_getEnglishMustReciteBookDataTimeout()
        {
            if(listen_root.state === "must_recite")
            {
                globalUI.hideLoading2();
                listen_root.state = "load_falied";
                loadFailed_resState = 4;
            }
        }

        function onSig_getEnglishSynBookDataError()
        {
            globalUI.hideLoading2();
            listen_root.state = "load_falied";
        }

        function onSig_getEnglishSceneExampleBookDataError()
        {
            globalUI.hideLoading2();
            listen_root.state = "load_falied";
        }

        function onSig_getEnglishListenExaminationError()
        {
            globalUI.hideLoading2();
            listen_root.state = "load_falied";
        }

        function onSig_bookHasDisappeared()
        {
            globalUI.hideLoading2();
            globalUI.showBottomSnackbar(true,qsTr("该专辑已下线，去听一下其他专辑吧"),Style.pixelSize24,qsTr(""),"")
        }

        function onSig_getEnglishWordDetailDataNull()
        {
            globalUI.hideLoading2();
            globalUI.showBottomSnackbar(true,qsTr("该课本无数据"),Style.pixelSize24,qsTr(""),"")
        }

        function onSig_getEnglishWordDetailError()
        {
            globalUI.hideLoading2();
            globalUI.showBottomSnackbar(true,qsTr("网络请求失败，请重试"),Style.pixelSize24,qsTr(""),"")
        }

        function onSig_getEnglishAudioDetailError()
        {
            globalUI.hideLoading2();
            globalUI.showBottomSnackbar(true,qsTr("网络请求失败，请重试"),Style.pixelSize24,qsTr(""),"")
        }

        function onSig_getEnglishListenExaminationSrtError()
        {
            globalUI.hideLoading2();
            globalUI.showBottomSnackbar(true,qsTr("网络请求失败，请重试"),Style.pixelSize24,qsTr(""),"")
        }

        function onSig_getEnglishHistoryError()
        {
            globalUI.hideLoading2();
            listen_root.state = "load_falied";
        }

        function onSig_getEnglistMustReciteBookDataError()
        {
            globalUI.hideLoading2();
            listen_root.state = "load_falied";
        }
    }

    Timer
    {
        id:switch_state_timer
        repeat: false
        interval: 1
        onTriggered:
        {
            listen_root.state = "net_error"
        }
    }

    function updateHistory()
    {
        console.log("updateHistory")

        if(netChannelManager.getNetState() === false)
        {
            switch_state_timer.start();
            return
        }

        if(enListenManager.getHistoryBookDataGetd() === false )
        {
            globalUI.showLoading2ClickHide("加载中");
            apiNetWork.sendApiGetEnglistStudyRecord();
        }
        else
        {
            updateGridContentByHistory();
        }
    }

    function updateSynWord()
    {
        console.log("updateSynWord")

        if(netChannelManager.getNetState() === false)
        {
            switch_state_timer.start();
            return
        }

        if(enListenManager.getSynBookListSize() === 0 )
        {
            mainSwipeView.currentItem.clearData();

            globalUI.showLoading2ClickHide("加载中");
            apiNetWork.sendApiGetEnglistProductList(1,enListenManager.getGrade());
        }
        else
        {
            updateGridContentBySynWord();
        }
    }


    function updateSceneExample()
    {
        console.log("updateSceneExample")

        if(netChannelManager.getNetState() === false)
        {
            switch_state_timer.start();
            return
        }

        if(enListenManager.getSceneExampleBookListSize() === 0 )
        {
            mainSwipeView.currentItem.clearData();

            globalUI.showLoading2ClickHide("加载中");
            apiNetWork.sendApiGetEnglistProductList(3);
        }
        else
        {
            updateGridContentBySceneExample();
        }
    }

    function updateMustRecite()
    {
        console.log("updateMustRecite")

        if(netChannelManager.getNetState() === false)
        {
            switch_state_timer.start();
            return
        }

        if(enListenManager.getMustReciteBookListSize() === 0 )
        {
            mainSwipeView.currentItem.clearData();

            globalUI.showLoading2ClickHide("加载中");
            apiNetWork.sendApiGetMustReciteProductList(10013);
        }
        else
        {
            updateGridContentByMustRecite();
        }
    }

    function updateListenExamination()
    {
        console.log("updateListenExamination")

        if(netChannelManager.getNetState() === false)
        {
            switch_state_timer.start();
            return
        }

        if(enListenManager.getListenExaminationListSize() === 0 )
        {
            mainSwipeView.currentItem.clearData();

            globalUI.showLoading2ClickHide("加载中");
            apiNetWork.sendApiGetEnglistProductList(26);
        }
        else
        {
            updateGridContentByListenExamination();
        }
    }

    function clearMainSwipePages()
    {
        var count = mainSwipeView.count
        for(var index = 0;index <count;index++)
        {
            mainSwipeView.takeItem(0);
        }
    }

    function preInit()
    {
        if (enListenManager.getLastTabIndex() !== 0 && enListenManager.getHistoryBookDataGetd() === false)
        {
            isNeedPreinit = true
            updateHistory()
        }
        else
        {
            isNeedPreinit = false
            init()
        }
    }

    function init()
    {
        requestGradeName = enListenManager.getGradeStr();
        console.log("Component.onCompleted 2")
        var tabIndex = enListenManager.getLastTabIndex();
        console.log("Component.onCompleted",tabIndex)
        switch(tabIndex)
        {
        case 0:
            listen_root.state = "history"
            break;
        case 1:
            listen_root.state = "syn_word"
            break;
        case 2:
            listen_root.state = "scene_example"
            break;
        case 3:
            listen_root.state = "must_recite"
            break;
        case 4:
            listen_root.state = "listen_examination"
            break;
        }
        menuList.currentIndex = tabIndex
        mainUI.bgChanged = true;
    }

    Component.onCompleted:
    {
        console.error("Component.onCompleted isbind=", firmwareManager.isbind)

        if (mainSwipeView.count === 0) {
            for (var i = 0; i < 5; i++) {
                var item = dynamicPageComponent.createObject(mainSwipeView, {})
                mainSwipeView.addItem(item)
            }
        }

        devStateMonitor.setAppModel(DevStatus.UI_EnglishListen);
        if(firmwareManager.isbind === false)
        {
            globalUI.loadQrPage(true,function(){
                            sig_back();
                            globalUI.closeQrPage();
                        },
                        function(){
                            preInit();
                        }
                            ,false);
        }
        else
        {
            preInit();
        }



        //pingManager.addPingData(PingDefine.PING_EVENT_ENTER_BOOKSCAN);
    }

    Component.onDestruction:
    {
        mainUI.bgChanged = false;
        GlobalProperty.accH5Opend = false;
        enListenManager.setIsPlaying(false);
    }

}
