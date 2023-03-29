import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    width: 900
    height: 400

    //表格宽度
    property var tableWidth: 906

    //列高
    property real itemHeigt: 35

    Rectangle {
        id: backgRect
        anchors.fill: parent
        color: "transparent"
        border.color: "#1A292D"
    }

    //表格 列头
    Item {
        id: headItem
        width: tableWidth
        height: itemHeigt
        anchors.left: backgRect.left
        anchors.leftMargin: 1
        anchors.top: parent.top

        Row {
            anchors.fill: parent
            spacing: -1

            Rectangle {
                id: headNumRect
                width: tableWidth * 0.1
                height: itemHeigt
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
                width: tableWidth * 0.15
                height: itemHeigt
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
                width: tableWidth * 0.15
                height: itemHeigt
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
                width: tableWidth * 0.15
                height: itemHeigt
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
                width: tableWidth * 0.15
                height: itemHeigt
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
                width: tableWidth * 0.15
                height: itemHeigt
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
                id: headOptRect
                width: tableWidth * 0.15
                height: itemHeigt
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
        width: tableWidth
        height: parent.height - headItem.height
        anchors.top: headItem.bottom
        anchors.topMargin: -1
        anchors.left: headItem.left
        model: UserInfoModel
        clip: true
        maximumFlickVelocity: itemHeigt * 10
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds
        spacing: -1
        cacheBuffer: itemHeigt * 10

        ScrollBar.vertical : ScrollBar {}

        delegate: Item {
            id: listItem
            width: tableWidth
            height: itemHeigt
            implicitWidth: tableWidth
            implicitHeight: itemHeigt

            //序号
            Rectangle {
                id: numberRect
                width: headNumRect.width
                height: itemHeigt
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
                height: itemHeigt
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: numberRect.right
                anchors.leftMargin: -1

                Text {
                    text: userTagID
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
                height: itemHeigt
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
                height: itemHeigt
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
                height: itemHeigt
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
                height: itemHeigt
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

            //操作
            Rectangle {
                id: optRect
                width: headOptRect.width
                height: itemHeigt
                color: "transparent"
                border.color: "#1A292D"
                anchors.left: roleRect.right
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
                        InterAction.delUserByUserID(userID)
                    }
                }
            }
        }
    }
}
