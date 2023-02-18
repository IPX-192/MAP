import QtQuick 2.0
import QtQuick.Controls 2.5

Popup {
    id: editTagPopup

    property bool bEditPopup: false

    onBEditPopupChanged: clearInput()

    width: 1000
    height: 600
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    background: Rectangle {
        anchors.fill: parent
        color: "lightblue"
    }

    onOpened: {
        //加载所有人员信息
        InterAction.loadAllUser()
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

    UserMagListView{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titeText.bottom
        anchors.topMargin: 40
        visible: !bEditPopup
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        spacing: 20

        Button {
            id: popupBtn
            width: 150
            height: 35
            text: "添加人员"
            visible: !bEditPopup
            onClicked: {
                bEditPopup = true
            }
        }

        Button {
            id: addBtn
            width: 150
            height: 35
            text: "添加人员"
            visible: bEditPopup
            onClicked: {
                addUser()
            }
        }

        Button {
            id: nextBtn
            width: 150
            height: 35
            text: "保存并添加下一个"
            visible: bEditPopup
            onClicked: {
                if(addUser())
                {
                    clearInput()
                }
            }
        }

        Button {
            id: closeBtn
            width: 150
            height: 35
            text: "关闭弹窗"
            onClicked: {
                close()
            }
        }
    }


    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titeText.bottom
        anchors.topMargin: 40
        spacing: 40
        visible: bEditPopup

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

        Text {
            id: tipText
            font.pixelSize: 12
            font.family: fontName
            color: "yellow"
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    function addUser()
    {
        if(userIDInput.text === "" || tagIDInput.text === "")
        {
            tipText.text = "工号与标签ID为必填项"
            tipText.visible = true
        }
        else
        {
            //检查是否重复
            let bExist = InterAction.isExist(userIDInput.text, tagIDInput.text)

            if(bExist)
            {
                tipText.text = "工号或标签ID已存在，无法重复添加"
                tipText.visible = true
                return false
            }

            //调用数据库添加
            let bSucess = InterAction.insert(nameInput.text, userIDInput.text, departmentInput.text,
                                            roleInput.text, tagIDInput.text)

            tipText.text = bSucess ? "添加成功" : "添加失败"
            tipText.visible = true
            return bSucess
        }
    }

    function clearInput()
    {
        nameInput.text = ""
        userIDInput.text = ""
        departmentInput.text = ""
        roleInput.text = ""
        tagIDInput.text = ""
    }

}
