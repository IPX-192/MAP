import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12


Popup {

    property var factorX :1.0
    property var factorY :1.0
    property var factor  :1.0
    property bool bGender:true

    id:devicePopup
    width: 1000
    height: 600
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape

    Text {
        id:addDevText
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 20
        text: qsTr("请选择添加方式：")
        font.pixelSize: 20
        font.family: fontName
        color: "#FEFEFE"
    }

    RadioButton {
        id: nextBtn
        text: qsTr("正序添加")
        checked: true
        anchors.left: addDevText.right
        anchors.leftMargin: 20 * factorX
        anchors.verticalCenter: addDevText.verticalCenter

        indicator: Rectangle {
            implicitWidth: 30 * factor
            implicitHeight: 30 * factor
            x: nextBtn.leftPadding
            y: parent.height / 2 - height / 2
            radius: width / 2
            border.color: nextBtn.checked ? "#FFFFFF" : "#666666"
            color: nextBtn.checked ? "#004640" : "#000002"

            Rectangle {
                width: 12 * factor
                height: 12 * factor
                x: 9 * factor  //(30 - 12) / 2
                y: 9 * factor
                radius: 6
                color: "#FFFFFF"
                visible: nextBtn.checked
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    nextBtn.checked  = true
                    bGender = true
                }
            }
        }

        contentItem: Text {
            text: nextBtn.text
            font{family: fontName; pixelSize: 16 * factor;}
            color: "#D6D6D6"
            verticalAlignment: Text.AlignVCenter
            leftPadding: nextBtn.indicator.width + 9 * factor
        }
    }

    RadioButton {
        id: preBtn
        text: qsTr("逆序添加")
        anchors.left: nextBtn.right
        anchors.leftMargin: 85 * factorX
        anchors.verticalCenter: nextBtn.verticalCenter

        indicator: Rectangle {
            implicitWidth: 30 * factor
            implicitHeight: 30 * factor
            x: nextBtn.leftPadding
            y: parent.height / 2 - height / 2
            radius: width / 2
            border.color: nextBtn.checked ? "#FFFFFF" : "#666666"
            color: nextBtn.checked ? "#004640" : "#000002"


            Rectangle {
                width: 12 * factor
                height: 12 * factor
                x: 9 * factor  //(30 - 12) / 2
                y: 9 * factor
                radius: 6
                color: "#FFFFFF"
                visible: preBtn.checked
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    preBtn.checked  = true
                    bGender = false
                }
            }
        }

        contentItem: Text {
            text: preBtn.text
            font{family: fontName; pixelSize: 16 * factor;}
            color: "#D6D6D6"
            verticalAlignment: Text.AlignVCenter
            leftPadding: preBtn.indicator.width + 9 * factor
        }

    }

    Button {
        id: closeBtn
        width: 200
        height: 35
        text: "关闭弹窗"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        onClicked: {
            close()
        }
    }

    background: Rectangle{
        anchors.fill: parent
        color: "#061215"

    }


}
