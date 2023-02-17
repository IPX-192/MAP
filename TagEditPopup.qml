import QtQuick 2.0
import QtQuick.Controls 2.5

Popup {
    id: editTagPopup
    width: 1000
    height: 600
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
        anchors.topMargin: 15
        text: qsTr("标签信息设置")
        font.bold: true
        font.pixelSize: 30
        font.family: fontName
        color: "#FEFEFE"
    }

    Column {
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.top: titeText.bottom
        anchors.topMargin: 40
        spacing: 20

        Item {
            id: name
            width: 300
            height: 35
            Text {
                id: nameText
                text: qsTr("姓名:")
                font.pixelSize: 16
                font.family: fontName
                color: "#FEFEFE"
            }
            TextField {
                id: nameInput
                placeholderTextColor:"#EEEEEE"
                anchors.right: parent.right
                width: 200
                height: 35
                hoverEnabled: true
                placeholderText: "请输入姓名"
                font.pixelSize: 16
                anchors.verticalCenter: nameText.verticalCenter
                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 35
                    radius: 10
                    color:"white"
                    border.color: "black"
                }
            }
        }

        Item {
            id: userID
            width: 300
            height: 35
            Text {
                id: userIDText
                text: qsTr("*工号:")
                font.pixelSize: 16
                font.family: fontName
                color: "#FEFEFE"
            }
            TextField {
                id: userIDInput
                placeholderTextColor:"#EEEEEE"
                anchors.right: parent.right
                width: 200
                height: 35
                hoverEnabled: true
                placeholderText: "请输入工号"
                font.pixelSize: 16
                anchors.verticalCenter: userIDText.verticalCenter
                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 35
                    radius: 10
                    color:"white"
                    border.color: "black"
                }
            }
        }

        Item {
            id: department
            width: 300
            height: 35
            Text {
                id: departmentText
                text: qsTr("工作队:")
                font.pixelSize: 16
                font.family: fontName
                color: "#FEFEFE"
            }
            TextField {
                id: departmentInput
                placeholderTextColor:"#EEEEEE"
                anchors.right: parent.right
                width: 200
                height: 35
                hoverEnabled: true
                placeholderText: "请输入工作队"
                font.pixelSize: 16
                anchors.verticalCenter: departmentText.verticalCenter
                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 35
                    radius: 10
                    color:"white"
                    border.color: "black"
                }
            }
        }


        Item {
            id: role
            width: 300
            height: 35
            Text {
                id: roleText
                text: qsTr("职务:")
                font.pixelSize: 16
                font.family: fontName
                color: "#FEFEFE"
            }
            TextField {
                id: roleInput
                placeholderTextColor:"#EEEEEE"
                anchors.right: parent.right
                width: 200
                height: 35
                hoverEnabled: true
                placeholderText: "请输入职务"
                font.pixelSize: 16
                anchors.verticalCenter: roleText.verticalCenter
                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 35
                    radius: 10
                    color:"white"
                    border.color: "black"
                }
            }
        }


        Item {
            id: tagID
            width: 300
            height: 35
            Text {
                id: tagIDText
                text: qsTr("标签ID:")
                font.pixelSize: 16
                font.family: fontName
                color: "#FEFEFE"
            }
            TextField {
                id: tagIDInput
                placeholderTextColor:"#EEEEEE"
                anchors.right: parent.right
                width: 200
                height: 35
                hoverEnabled: true
                placeholderText: "请输入标签ID"
                font.pixelSize: 16
                anchors.verticalCenter: tagIDText.verticalCenter
                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 35
                    radius: 10
                    color:"white"
                    border.color: "black"
                }
            }
        }
    }

    Text {
        id: tipText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: saveBtn.top
        anchors.bottomMargin: 15
        font.bold: true
        font.pixelSize: 20
        font.family: fontName
        color: "yellow"
        visible: false
    }

    Button {
        id: saveBtn
        width: 200
        height: 35
        text: "完成添加"
        anchors.left: parent.left
        anchors.leftMargin: 50

        anchors.bottom: nextBtn.top
        anchors.bottomMargin: 20
        onClicked: {
            if(userIDInput.text === "" || tagIDInput.text === "")
            {
                tipText.text = "工号与标签ID为必填项"
                tipText.visible = true
            }
            else
            {
                //调用数据库添加

                //添加成功
                close()
            }
        }
    }

    Button {
        id: nextBtn
        width: 200
        height: 35
        text: "保存并添加下一个"
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.bottom: closeBtn.top
        anchors.bottomMargin: 20
        onClicked: {
            if(userIDInput.text === "" || tagIDInput.text === "")
            {
                tipText.text = "工号与标签ID为必填项!"
                tipText.visible = true
            }
            else
            {
                //调用数据库添加

                //清空当前输入
                nameInput.text = ""
                userIDInput.text = ""
                departmentInput.text = ""
                roleInput.text = ""
                tagIDInput.text = ""
            }
        }
    }

    Button {
        id: closeBtn
        width: 200
        height: 35
        text: "取消添加"
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        onClicked: {
            close()
        }
    }

    UserMagListView{
        anchors.right: parent.right
        anchors.top: titeText.bottom
        anchors.topMargin: 40
    }

}
