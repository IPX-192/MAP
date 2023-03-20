import QtQuick 2.0
import QtQuick.Controls 2.5

Popup {
    id: dataViewPopup
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
        InterAction.loadAllTagData()
    }

    Text {
        id: titeText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 15
        text: qsTr("标签数据明细")
        font.bold: true
        font.pixelSize: 30
        font.family: fontName
        color: "#FEFEFE"
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
            dataViewPopup.close()
        }
    }

    Rectangle {
        id: backgRect
        width: 900
        height: 400
        color: "transparent"
        border.color: "#1A292D"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titeText.bottom
        anchors.topMargin: 40
    }

    //表格 列头
    Item {
        id: headItem
        width: 908
        height: 35
        anchors.left: backgRect.left
        anchors.leftMargin: 1
        anchors.top: backgRect.top

        Row {
            anchors.fill: parent
            spacing: -1

            Rectangle {
                id: headNumRect
                width: 908 * 0.06
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    id: headText
                    text: "序号"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }


            Rectangle {
                id: headTagIdRect
                width: 908 * 0.11
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    id: headIDText
                    text: "TagID"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headNameRect
                width: 908 * 0.07
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "姓名"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headIDRect
                width: 908 * 0.11
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "工号"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headDeptRect
                width: 908 * 0.10
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "工作队"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headRoleRect
                width: 908 * 0.12
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "职务"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headPosXRect
                width: 908 * 0.11
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "坐标X(mm)"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headPosYRect
                width: 908 * 0.11
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "坐标Y(mm)"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headBatteryYRect
                width: 908 * 0.06
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "电量"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headTimeRect
                width: 908 * 0.09
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "静止时间"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }


            Rectangle {
                id: headOptRect
                width: 908 * 0.06
                height: 35
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "操作"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

        }
    }

    ListView{
        id: userInfoListiew
        width: 908
        height: backgRect.height - headItem.height
        anchors.top: headItem.bottom
        anchors.topMargin: -1
        anchors.left: headItem.left
        model: TagDataModel
        clip: true
        maximumFlickVelocity: 350
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds
        spacing: -1

        delegate: Item {
            id: listItem
            width: 908
            height: 35
            implicitWidth: 908
            implicitHeight: 35

            //序号
            Rectangle {
                id: numberRect
                width: headNumRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: parent.left

                Text {
                    id: numText
                    text: index + 1
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //TagID
            Rectangle {
                id: tagIDRect
                width: headTagIdRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: numberRect.right
                anchors.leftMargin: -1

                Text {
                    text: tagID
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //姓名
            Rectangle {
                id: nameRect
                width: headNameRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: tagIDRect.right
                anchors.leftMargin: -1

                Text {
                    text: userName
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //工号
            Rectangle {
                id: idRect
                width: headIDRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: nameRect.right
                anchors.leftMargin: -1

                Text {
                    text: userID
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //工作队
            Rectangle {
                id: depatmentRect
                width: headDeptRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: idRect.right
                anchors.leftMargin: -1

                Text {
                    text: department
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //职务
            Rectangle {
                id: roleRect
                width: headRoleRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: depatmentRect.right
                anchors.leftMargin: -1

                Text {
                    text: userRole
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //坐标x
            Rectangle {
                id: posXRect
                width: headPosXRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: roleRect.right
                anchors.leftMargin: -1

                Text {
                    text: posX
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //坐标y
            Rectangle {
                id: posYRect
                width: headPosYRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: posXRect.right
                anchors.leftMargin: -1

                Text {
                    text: posY
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //电量
            Rectangle {
                id: batteryRect
                width: headBatteryYRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: posYRect.right
                anchors.leftMargin: -1

                Text {
                    text: battery
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //静止时间
            Rectangle {
                id: timeRect
                width: headTimeRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: batteryRect.right
                anchors.leftMargin: -1

                Text {
                    text: staticTime
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#000000"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //操作
            Rectangle {
                id: optRect
                width: headOptRect.width
                height: 35
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: timeRect.right
                anchors.leftMargin: -1

                Text {
                    text: "删除"
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#FFC061"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        InterAction.delTagData(dataID)
                    }
                }
            }

        }
    }

}
