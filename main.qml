import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("定位软件")


    Rectangle{
        id:title
        width: 100
        height: 50
        color: "red"
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 30

        Text {
            anchors.centerIn: parent
            text: qsTr("定位系统")
        }
    }

    //配置按钮

    Rectangle {
        id:configBtn
        width: 50
        height: width
        radius: width / 2
        color: "white"
        anchors.verticalCenter:title.verticalCenter
        anchors.left: title.right
        anchors.leftMargin: 600
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


    //定位显示区域

}
