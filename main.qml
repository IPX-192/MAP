import QtQuick 2.12
import QtQuick.Window 2.12

Window {

    visible: true
    width: 1270
    height: 768
    title: qsTr("定位软件")
    property bool bSetOrigin:false

    readonly property string  fontName:  qsTr("Microsoft YaHei")  // 字体名字

    property string ipAddress: ""

    property int originX: 40   //原点X

    property int originY: 40  //原点Y

    //flags: Qt.FramelessWindowHint | Qt.Window

    FontLoader{
        id: localFont1
        source: "qrc:/font/MFYueYuan.ttf"
    }

    ///
    //顶部栏
    Rectangle{

        id:title
        width: parent.width
        height: 80
        color: "#2E529B"
        anchors.top: parent.top
        anchors.topMargin: 10

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

        Rectangle {
            id:configBtn
            width: 50
            height: width
            radius: width / 2
            color: "white"
            anchors.verticalCenter:logoImg.verticalCenter
            anchors.left: logoImg.right
            anchors.leftMargin: 500
            border.color: "black"
            Text {
                anchors.centerIn: parent
                text: qsTr("配置")
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    systemSettingLoader.visible = !systemSettingLoader.visible
                    if(systemSettingLoader.visible)
                    {
                        hideSetTimer.start()
                    }
                    else
                    {
                        hideSetTimer.stop()
                    }
                }
            }

        }

        //系统设置菜单
        Loader
        {
            id : systemSettingLoader
            visible: false
            anchors.horizontalCenter: configBtn.horizontalCenter
            anchors.top: configBtn.bottom
            anchors.topMargin: 20
            z:20
            source: "qrc:/SystemConfig.qml"
        }

        Connections{
            target: systemSettingLoader.item
            onSetBtnClicked:{
                systemSettingLoader.visible = false
                hideSetTimer.stop()

                 console.log("seeeeeeeeeeeeeee" + index)
                //上传图片
                if(index === 0)
                {
                    imageLoader.setSource("qrc:/FileDialog.qml",{"fileDialog_Title":qsTr("选择图片"),
                                              "fileDialog_Visible":true,"fileDialog_NameFilter":["Image Files (*.png *.jpg)"],
                                          } )
                }

                //设置原点
                if(index === 4)
                {

                    bSetOrigin = true
                }
                else
                {
                    // openTagEditPopup()
                }
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

    //表格
    Rectangle {
        width: 500
        height: 300
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: title.bottom
        anchors.topMargin: 20
        color: "lightblue"

        //        UserInfoListView {
        //            anchors.fill: parent
        //        }
    }



    //定位显示区域
    Item {
        id:mapItem
        width: 500
        height: 200
        anchors.left: title.left
        anchors.leftMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100

        Rectangle{
            id:imageDisplay

            width:parent.width
            height:parent.height
            border.color: "black"
            z:-10

            Image {
                id:usrImg
                anchors.fill: parent
                source: "qrc:/iamge/testMap.png"
                fillMode: Image.PreserveAspectCrop;


                //原点图片
                Image{
                    id:originImg
                    width: 25
                    height: 25
                    x:originX
                    y:originY
                    source: "qrc:/iamge/origin.png"
                }


                //坐标图片
                Image {
                    id:coordImg
                    width: 34
                    height: 34
                    x:parent.width / 2
                    y:parent.height /2
                    //anchors.centerIn: parent
                    source: "qrc:/iamge/coord.png"
                }

                ///使用wheelEvent控制滚轮，其中angleDelta属性用来获取滚轮滚动的距离
                MouseArea{
                    anchors.fill: parent
                    onWheel: {
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

            ///使用wheelEvent控制滚轮，其中angleDelta属性用来获取滚轮滚动的距离
            //            MouseArea{
            //                anchors.fill: parent
            //                onWheel: {
            //                    if (wheel.modifiers & Qt.ControlModifier) {
            //                        imageDisplay.rotation += wheel.angleDelta.y / 120 * 5;
            //                        if (Math.abs(imageDisplay.rotation) < 4)
            //                            imageDisplay.rotation = 0;
            //                    }
            //                    else {
            //                        imageDisplay.rotation += wheel.angleDelta.x / 120;
            //                        if (Math.abs(imageDisplay.rotation) < 0.6)
            //                            imageDisplay.rotation = 0;
            //                        var scaleBefore = imageDisplay.scale;
            //                        imageDisplay.scale += imageDisplay.scale * wheel.angleDelta.y / 120 / 10;
            //                    }
            //                }
            //            }
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
                    console.log("mouseX " + mouse.x)
                    console.log("mouseY " + mouse.y)
                    originX = mouseX - originImg.width / 2
                    originY = mouseY - originImg.height / 2
                }
                else
                {
                    cursorShape = Qt.ArrowCursor
                }
            }
        }


        Connections{
            target: InterAction
            //设置人的坐标
            onSetCurCoord:{

                if( originX + originImg.width / 2  + coordX - coordImg.width / 2 < 0)
                {
                    coordImg.x = originX + originImg.width / 2  + coordX - coordImg.width / 2
                }
                else
                {
                    coordImg.x = originX + coordX - coordImg.width / 2
                }

                if(originY +  originImg.height / 2 +  coordY - coordImg.height / 2 < 0)
                {
                    coordImg.y = originY + originImg.height / 2
                }

                else
                {
                    coordImg.y = originY +  originImg.height / 2 +  coordY - coordImg.height / 2
                }
            }
        }
    }


    //底部栏
    Rectangle{
        width: title.width
        height: 50
        color: title.color
        anchors.bottom: parent.bottom

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            text: qsTr("服务器地址") + ipAddress
            font.pixelSize: 22
            font.family: fontName
            color: "#FEFEFE"
        }
    }

    Connections{
        target: InterAction
        onSendCurServerAddress:{
            ipAddress = address
            console.log("bbbbbbbbbbbbbbbbbbbbbbbbbbbb" + ipAddress)
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

}
