import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Item {
    //弹出窗口的Title栏

    property string titleText: ""

    signal popupClose()

    width: parent.width
    height: 40

    signal sigCloseBtnClicked()

    Rectangle
    {
        id : popTitle
        width: parent.width
        height: 40
        color: "#48595D"
        anchors.top: parent.top
        anchors.left: parent.left
        Text
        {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            text: qsTr( titleText )
            color: "#FFFFFF"
            font{family: "Microsoft YaHei"; pixelSize: 18; bold : true}
        }

        //关闭按钮
        Rectangle
        {
            id: closeBtn
            width: 40
            height: width
            color: "#465169"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            Image {
                id: closeImage
                source: "qrc:/iamge/close2.png"
                anchors.centerIn: parent
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:{

                    popupClose()
                    sigCloseBtnClicked()
                }
            }
        }
    }
}
