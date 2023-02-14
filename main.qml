import QtQuick 2.12
import QtQuick.Window 2.12

Window {

    visible: true
    width: 1270
    height: 768
    title: qsTr("定位软件")
    property bool bSetOrigin:false

    readonly property string  fontName:  qsTr("Microsoft YaHei")  // 字体名字

    //flags: Qt.FramelessWindowHint | Qt.Window

    FontLoader{
        id: localFont1
        source: "qrc:/font/MFYueYuan.ttf"
    }


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
            anchors.topMargin: 30
            z:20
            source: "qrc:/SystemConfig.qml"
        }

        Connections{
            target: systemSettingLoader.item
            onSetBtnClicked:{
                console.log("sdadasdasd" + index)
                if(index === 1)
                {
                    bSetOrigin = true
                }
            }
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

        UserInfoListView {
            anchors.fill: parent
        }
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

        Image {
            anchors.fill: parent
            source: "qrc:/iamge/testMap.png"
            fillMode:Image.PreserveAspectCrop
        }

        //原点图片
        Image{
            id:originImg
            width: 25
            height: 25
            x:40
            y:40
            source: "qrc:/iamge/origin.png"
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
                    originImg.x = mouseX - originImg.width / 2
                    originImg.y = mouseY - originImg.height / 2
                }
                else
                {
                    cursorShape = Qt.ArrowCursor
                }
            }
        }
    }

}
