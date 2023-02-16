import QtQuick 2.0

import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0


Item {

    id : root
    visible: true
    width: 120
    height: 260

    signal setBtnClicked( var index )


    Rectangle
    {
        id: menuRect
        width: 120
        height: 260
        radius: 10
        color: "white"
        border.width: 1
        border.color: "black"
        anchors.fill: parent

        Column
        {
            spacing: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater
            {
                model: [ qsTr( "导入地图" ), qsTr( "人员信息配置" ),,qsTr( "历史数据" ), qsTr( "地图原点配置" )]
                Rectangle
                {
                    width: 100
                    height: 45
                    color: "yellow"
                    enabled:setBtnEnable(index)
                    opacity: enabled ? 1: 0.5
                    z:10
                    Text {
                        id: displayText
                        text: qsTr( modelData )
                        font{ pixelSize: 20 ; family: "Microsoft YaHei"; bold: true}
                        color: "blue"
                        anchors.centerIn: parent
                    }
                    Image {
                        id: line
                        visible: index === 1 ? false : true
                        width: parent.width
                        height: 2
                        fillMode: Image.PreserveAspectCrop
                        anchors.top: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "qrc:/image/line.png"
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: displayText.color = "#1ADDFC"
                        onExited: displayText.color = "yellow"
                        onClicked:
                        {
                            setBtnClicked( index )
                        }
                    }
                }
            }
        }

    }
}
