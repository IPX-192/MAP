import QtQuick 2.0

Item {
    width: 1000
    height: 300

    //表格宽度
    property var tableWidth: 1000

    //列高
    property real itemHeigt: 35


    //表格 列头
    Item {
        id: headItem
        width: tableWidth
        height: itemHeigt
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        Row {
            anchors.fill: parent
            spacing: -1

            Rectangle {
                id: headNumRect
                width: tableWidth * 0.05
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
                width: tableWidth * 0.1
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
                width: tableWidth * 0.12
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
                width: tableWidth * 0.12
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
                width: tableWidth * 0.12
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
                id: headCoordXRect
                width: tableWidth * 0.1
                height: itemHeigt
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "坐标x(mm)"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headCoordYRect
                width: tableWidth * 0.1
                height: itemHeigt
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "坐标y(mm)"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            //设备位置
            Rectangle {
                id: headDevRect
                width: tableWidth * 0.09
                height: itemHeigt
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    text: "设备位置"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headKwhRect
                width: tableWidth * 0.05 + 8
                height: itemHeigt
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
        }
    }

    ListView{
        id: userInfoListiew
        width: tableWidth
        height: parent.height - headItem.height
        anchors.top: headItem.bottom
        anchors.topMargin: -1
        anchors.left: headItem.left
        model: OnlineTagModel
        clip: true
        maximumFlickVelocity: itemHeigt * 10
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds
        spacing: -1

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
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: parent.left

                Text {
                    id: numText
                    text: index + 1
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
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
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: numberRect.right
                anchors.leftMargin: -1

                Text {
                    text: tagID
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
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
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: tagIDRect.right
                anchors.leftMargin: -1

                Text {
                    text: userName
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
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
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: nameRect.right
                anchors.leftMargin: -1

                Text {
                    text: userID
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
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
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: idRect.right
                anchors.leftMargin: -1

                Text {
                    text: department
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
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
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: depatmentRect.right
                anchors.leftMargin: -1

                Text {
                    text: userRole
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //坐标x
            Rectangle {
                id: posXRect
                width: headCoordXRect.width
                height: itemHeigt
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: roleRect.right
                anchors.leftMargin: -1

                Text {
                    text: posX
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //坐标y
            Rectangle {
                id: posYRect
                width: headCoordYRect.width
                height: itemHeigt
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: posXRect.right
                anchors.leftMargin: -1

                Text {
                    text: posY
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //设备位置
            Rectangle {
                id: devRect
                width: headDevRect.width
                height: itemHeigt
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: posYRect.right
                anchors.leftMargin: -1

                Text {
                    text: posZ  //暂时用Z代替
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            //电量
            Rectangle {
                id: batteryRect
                width: headKwhRect.width
                height: itemHeigt
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: devRect.right
                anchors.leftMargin: -1

                Text {
                    text: battery
                    width: parent.width
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                    fontSizeMode: Text.Fit
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }
}
