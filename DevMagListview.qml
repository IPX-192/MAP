import QtQuick 2.0
import QtQuick 2.12

Item {

    width: 500
    height: 300

    //表格宽度
    property var tableWidth: 500

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
                id: headDevNumRect
                width: tableWidth * 0.5
                height: itemHeigt
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    id: headDevNumText
                    text: "设备号1"
                    font.pixelSize: 16
                    font.family: "Microsoft YaHei"
                    font.bold: true
                    color: "#D6D6D6"
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: headDevWidthRect
                width: tableWidth * 0.5
                height: itemHeigt
                color: "#2E529B"
                border.color: "#49649B"

                //普通表头框
                Text {
                    id: headDevWidthText
                    text: "设备位置"
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
        id: devInfoListiew
        width: tableWidth
        height: parent.height - headItem.height
        anchors.top: headItem.bottom
        anchors.topMargin: -1
        anchors.left: headItem.left
        model: DevInfoModel
        clip: true
        maximumFlickVelocity: 1000
        //flickableDirection: Flickable.VerticalFlick
        //boundsBehavior: Flickable.StopAtBounds
        interactive:true
        snapMode: ListView.NoSnap
        spacing: -1

        delegate: Item {
            id: listItem
            width: tableWidth
            height: itemHeigt
            implicitWidth: tableWidth
            implicitHeight: itemHeigt

            //设备标号
            Rectangle {
                id: devnumRect
                width: headDevNumRect.width
                height: itemHeigt
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: parent.left

                Text {
                    id: devnumText
                    text: devName
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
                id: devPosRect
                width: headDevWidthRect.width
                height: itemHeigt
                color: index % 2 === 0 ? "#213B42" : "#000000"
                border.color: "#1A292D"
                anchors.left: devnumRect.right

                Text {
                    id: devPosText
                    text: devPos
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
