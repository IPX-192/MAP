import QtQuick 2.0
import QtQuick.Controls 2.5

Popup {
    id: editTagPopup
    width: 895
    height: 380
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    background: Rectangle {
        anchors.fill: parent
        color: "lightblue"
    }

    Text {
        id: titeText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        text: qsTr("标签信息设置")
        font.bold: true
        font.pixelSize: 30
        font.family: fontName
        color: "#FEFEFE"
    }

    Item {
        id: name
        width: 100
        height: 70
        anchors.top: titeText.bottom
        anchors.topMargin: 20
        Text {
            id: nameText
            text: qsTr("姓名")
            font.pixelSize: 20
            font.family: fontName
            color: "#FEFEFE"
        }
        TextInput {
            text: qsTr("text")
            anchors.left: nameText.right
            anchors.leftMargin: 10
            width: 80
            height: parent.height
            anchors.verticalCenter: nameText.verticalCenter
        }

    }
}
