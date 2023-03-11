import QtQuick 2.12
import QtQuick.Window 2.12
import Charts 1.0
import QtQuick.Controls 2.5

Window {

    visible: true
    width: 1270
    height: 768
    title: qsTr("定位软件")
    property bool bSetOrigin:false

    property bool bSetLocalIp:false

    readonly property string  fontName:  qsTr("Microsoft YaHei")  // 字体名字

    property string ipAddress: ""

    property string connectStatus: "disconnected"

    property int originX: 40   //原点X

    property int originY: 80  //原点Y

    property var maxY:100

    property bool bSaveImg:false

    //flags: Qt.FramelessWindowHint | Qt.Window

    FontLoader{
        id: localFont1
        source: "qrc:/font/时尚中黑简体.ttf"
    }

    Rectangle{
        anchors.fill:parent
        color: "#050B14"
        Image {
            id: background
            source: "qrc:/iamge/background.png"

        }
    }

    AnimatedImage {
        anchors.left: parent.left
        anchors.top:title.bottom
        anchors.bottom: bottomItem.top
        source: "qrc:/iamge/leftaDorn.gif"
        z:10

    }

    AnimatedImage {
        anchors.right: parent.right
        anchors.top:title.bottom
        anchors.bottom: bottomItem.top
        source: "qrc:/iamge/rightDorn.gif"
        z:10
    }

    Component.onCompleted: {
        chart.setOriginCoord(originX ,maxY - originY)
        ipAddress = SocketServer.getLocalIP()
        bSaveImg = InterAction.isSaveImage()
        if(bSaveImg)
        {
            usrImg.source = InterAction.getImagePath()
        }
        else
        {
            usrImg.source = "qrc:/iamge/testMap.png"
        }
    }

    //顶部栏
    Rectangle{
        id:title
        width: parent.width
        height: 80
        color: "#062B3C"
        anchors.top: parent.top

        Image {
            anchors.fill: parent
            source: "qrc:/iamge/top.png"

        }

        Image{
            id:logoImg
            width: 50
            height: 50
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            source: "qrc:/iamge/log.png"
        }

        Text {
            id:titeText
            anchors.verticalCenter: logoImg.verticalCenter
            anchors.left: logoImg.right
            anchors.leftMargin: 20
            text: qsTr("定位系统")
            font.pixelSize: 22
            font.family: fontName
            color: "#FEFEFE"
        }

        //配置按钮
        Button {
            id: dataBtn
            width: 100
            height: 35
            text: "历史数据"
            font.family: fontName
            anchors.right: deviceSetBtn.left
            anchors.rightMargin: 20
            // highlighted:true

            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                dataPopup.open()
            }
        }

        Button {
            id: tagBtn
            width: 100
            height: 35
            text: "配置标签"
            font.family: fontName
            anchors.right: dataBtn.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                openTagEditPopup()
            }
        }

        Button {
            id: oringinBtn
            width: 100
            height: 35
            text: "配置原点"
            font.family: fontName
            anchors.right: tagBtn.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                bSetOrigin = !bSetOrigin
                if(bSetOrigin)
                {
                    oringinBtn.highlighted = true
                    oringinBtn.text  = qsTr("取消配置")
                }
                else
                {
                    oringinBtn.highlighted = false
                    oringinBtn.text  = qsTr("配置原点")
                }
            }
        }

        Button {
            id: importBtn
            width: 100
            height: 35
            font.family: fontName
            text: "导入地图"
            anchors.right: oringinBtn.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                imageLoader.setSource("qrc:/FileDialog.qml",{"fileDialog_Title":qsTr("选择图片"),
                                          "fileDialog_Visible":true,"fileDialog_NameFilter":["Image Files (*.png *.jpg)"],
                                      } )
            }
        }

        Button {
            id: deviceSetBtn
            width: 100
            height: 35
            font.family: fontName
            text: "设备配置"
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                devicePopup.open()
            }
        }
    }

    //上传图片
    Loader{
        id:imageLoader
    }

    //响应获取文件路径消息
    Connections
    {
        target: imageLoader.item
        onGetFileString:{
            usrImg.source = path
            InterAction.copyImageFile( path )
        }
    }

    Timer{
        id:hideSetTimer
        repeat: false
        interval: 5000
        onTriggered: {
            systemSettingLoader.visible = false
        }
    }

    Image {
        id: captionImage3
        anchors.left: usrInfo.left
        anchors.bottom: usrInfo.top
        anchors.bottomMargin: 20
        source: "qrc:/iamge/title.png"
    }

    Text {
        id: pointAnalysis1
        anchors.top: captionImage3.top
        anchors.left: captionImage3.left
        anchors.leftMargin: 13
        color: "#F0F0F0"
        text: qsTr("Tag标签信息")
        font{family:localFont1.name;pixelSize: 18;}
    }

    //表格
    Rectangle {
        id:usrInfo
        width: 1000
        height: 300
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: mapItem.bottom
        anchors.topMargin: 120
        color: "lightblue"

        UserInfoListView {
            anchors.fill: parent
        }
    }


    Image {
        id: captionImage4
        anchors.left: mapItem.left
        anchors.bottom: mapItem.top
        anchors.bottomMargin: 20
        source: "qrc:/iamge/title.png"
    }

    Text {
        id: pointAnalysis
        anchors.top: captionImage4.top
        anchors.left: captionImage4.left
        anchors.leftMargin: 13
        color: "#F0F0F0"
        text: qsTr("坐标显示图")
        font{family:localFont1.name;pixelSize: 18;}
    }

    //定位显示区域,居中显示
    Item {
        id:mapItem
        width: 1000
        height: 100

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: title.bottom
        anchors.topMargin: 80

        Rectangle{
            id:imageDisplay
            width:parent.width
            height:parent.height
            border.color: "black"

            Image {
                id:usrImg
                anchors.fill: parent
                source: "qrc:/iamge/testMap.png"
                fillMode: Image.PreserveAspectCrop;

                CUserCoordView{
                    id:chart
                    width: 1000
                    height: 100
                    anchors.centerIn: parent
                }


                Connections{
                    target: SocketServer
                    //设置人的坐标
                    onSetCurCoord:{
                        chart.setCurCoord(coordX,coordY,tagID);
                    }

                    //新收到消息时清理以往的显示
                    onClearDrawCoord:{
                        chart.clearVecCoord();
                    }
                }


                //原点图片
                Image{
                    id:originImg
                    width: 24
                    height: 24
                    x:originX - width / 2
                    y:originY - height / 2
                    source: "qrc:/iamge/origin.png"
                }

                ///使用wheelEvent控制滚轮，其中angleDelta属性用来获取滚轮滚动的距离
                MouseArea{
                    anchors.fill: parent
                    onWheel: {
                        return;
                        if (wheel.modifiers & Qt.ControlModifier) {
                            usrImg.rotation += wheel.angleDelta.y / 120 * 5;
                            if (Math.abs(usrImg.rotation) < 4)
                                usrImg.rotation = 0;
                        }
                        else {
                            usrImg.rotation += wheel.angleDelta.x / 120;
                            if (Math.abs(usrImg.rotation) < 0.6)
                                usrImg.rotation = 0;
                            var scaleBefore = usrImg.scale;
                            usrImg.scale += usrImg.scale * wheel.angleDelta.y / 120 / 10;
                        }
                    }

                    onClicked: {
                        console.log("现在鼠标点击的位置" + mouseX,mouseY)
                    }
                }
            }
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                //如果设置原点，改变鼠标样式
                if(bSetOrigin)
                {
                    cursorShape = Qt. CrossCursor
                }
                else
                {
                    cursorShape = Qt.ArrowCursor
                }
            }
            onClicked: {
                //如果设置原点,设置原点
                if(bSetOrigin)
                {
                    //console.log("mouseX " + mouse.x)
                    console.log("mouseY " + (maxY - mouse.y))

                    originX = mouse.x
                    originY = mouse.y

                    chart.setOriginCoord(originX ,maxY - mouse.y)
                }
                else
                {
                    cursorShape = Qt.ArrowCursor
                }
            }
        }
    }

    //设备显示
    Item {
        id: devItem
        width: mapItem.width
        height: 30
        anchors.left: mapItem.left
        anchors.top: mapItem.bottom
        anchors.topMargin: 5

        Repeater {
            width: parent.width
            height: parent.height
            model: DevInfoModel
            delegate: Rectangle {
                id: test
                x: devPos / 500
                y: 0
                width: 1
                height: 30
                color: model.bLight  ? "green" : "gray"
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        tooltip.visible = true
                    }
                    onExited: {
                        tooltip.visible = false
                    }
                }

                ToolTip {
                    id: tooltip
                    delay: 200
                    width: 50
                    y: parent.height
                    text: model.devName
                }
            }
        }

    }


    //底部栏
    Rectangle{
        id:bottomItem
        width: title.width
        height: 50
        color: title.color
        anchors.bottom: parent.bottom

        Rectangle{
            id:ipSetBtn
            width: 120
            height: 36
            color: parent.color
            anchors.verticalCenter: bottomItem.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            border.color: "#2E529B"
            radius: 6
            Image {
                id:ipSetImage
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                source: "qrc:/iamge/setClick.png"
            }

            Text {
                id:ipSetText
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: ipSetImage.right
                anchors.leftMargin: 10
                text: bSetLocalIp ? qsTr("LocalHost") : ("本机IP")
                font.pixelSize: 16
                font.family: fontName
                color: "#FEFEFE"
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    bSetLocalIp = !bSetLocalIp
                    SocketServer.stopServer()
                    bSetLocalIp ? SocketServer.startServer(true) : SocketServer.startServer(false)
                    ipAddress =   bSetLocalIp ? "127.0.0.1" : SocketServer.getLocalIP()

                    //改变布局
                    ipSetImage.source = bSetLocalIp ? "qrc:/iamge/set.png" : "qrc:/iamge/setClick.png"
                    ipSetBtn.border.color =  bSetLocalIp ? "#404142" : "#2E529B"
                }
            }
        }

        Text {
            id:ipAddressText
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: ipSetBtn.right
            anchors.leftMargin: 20
            text: qsTr("服务器地址: ") + ipAddress
            font.pixelSize: 18
            font.family: fontName
            color: "#FEFEFE"
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: ipAddressText.right
            anchors.leftMargin: 50
            text: qsTr("连接状态: ") + connectStatus
            font.pixelSize: 18
            font.family: fontName
            color: "#FEFEFE"
        }

        //服务器地址
        CusInputBox{
            id:serverInput
            width: 180
            height: 40
            anchors.right: parent.right
            anchors.rightMargin: 180
            anchors.verticalCenter: parent.verticalCenter
            tipsString:"请输入转发地址"
            maximumLength:15
        }

        //端口号
        CusInputBox{
            id:comInput
            width: 60
            height: 40
            anchors.left: serverInput.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            tipsString:"端口号"
            maximumLength:5
        }

        Button {
            id: serverBtn
            width: 60
            height: 30
            text: "转发"
            anchors.left: comInput.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            font.family: fontName
            onClicked: {

            }
        }

    }

    Timer{
        interval: 1500
        repeat:true
        running:true
        onTriggered:
        {
            var bStatus = SocketServer.getServerConnectStatus()
            connectStatus = bStatus ? qsTr("connected") : qsTr("disconnected")
        }
    }

    //标签编辑弹窗
    TagEditPopup {
        id: tagEidtTag
        anchors.centerIn: parent
    }

    function openTagEditPopup()
    {
        tagEidtTag.open()
    }

    function closeTagEditPoupu()
    {
        tagEidtTag.close()
    }

    //历史数据弹窗
    HistoryDataPopup {
        id: dataPopup
        anchors.centerIn: parent
    }

    //设备设置
    DeviceMagPopup{
        id:devicePopup
        anchors.centerIn: parent
    }



}
