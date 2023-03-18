import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12


Popup {
    id:deviceMag
    property var factorX :1.0
    property var factorY :1.0
    property var factor  :1.0
    property bool bNext:true
    property alias devMaxNum: maxDevInput.text
    property var devNum:0
    width: 1000
    height: 600
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    padding: 0

    property alias bRightOrder: nextBtn.checked

    onOpened: {
        InterAction.bResetTimerACtive(false)
        InterAction.loadDevINfo()
        devNum = InterAction.getDevNum()
        bNext = InterAction.bDevRightOrder()

        //        if(!bNext)
        //        {
        //            devMaxNum = String(InterAction.getDevMaxNum())
        //        }


        devNumTip.text = "最大设备数200,多个设备请分批次添加"
    }

    onClosed: {
        InterAction.bResetTimerACtive(true)
    }

    //弹出窗口的Title栏
    PopupTitle{
        id : popupTitle
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 1
        titleText: qsTr( "添加设备" )
    }

    Text {
        id:addDevText
        anchors.top: popupTitle.bottom
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 20
        text: qsTr("请选择添加方式：")
        font.pixelSize: 20
        font.family: fontName
        color: "#FEFEFE"
    }

    Text {
        id:maxDevText
        anchors.top: popupTitle.bottom
        anchors.topMargin: 30
        anchors.right: maxDevInput.left
        anchors.rightMargin: 20
        text: qsTr("最大设备号：")
        font.pixelSize: 20
        font.family: fontName
        color: "#FEFEFE"
    }

    CusInputBox{
        id:maxDevInput
        width: 100
        height: 50
        anchors.right: sureBtn.left
        anchors.rightMargin: 20
        anchors.verticalCenter: addDevText.verticalCenter
        enabled: !bNext && devNum === 0
        opacity: bNext ? 0.5 : 1
    }

    Button {
        id: sureBtn
        width: 60
        height: 30
        text: "确定"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: addDevText.verticalCenter
        font.family: fontName
        enabled: maxDevInput.enabled
        opacity: maxDevInput.opacity
        onClicked: {
            close()
        }
    }

    RadioButton {
        id: nextBtn
        text: qsTr("正序添加")
        checked: bNext
        anchors.left: addDevText.right
        anchors.leftMargin: 20 * factorX
        anchors.verticalCenter: addDevText.verticalCenter
        enabled: devNum === 0
        opacity: enabled ? 1 : 0.5

        MouseArea{
            anchors.fill: parent
            onClicked: {
                return
            }
        }

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
                propagateComposedEvents: true
                onClicked: {
                    nextBtn.checked  = true
                    bNext = true
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
        enabled: nextBtn.enabled
        opacity: nextBtn.opacity
        checked: !bNext
        MouseArea{
            anchors.fill: parent
            onClicked: {
                return
            }
        }

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
                propagateComposedEvents: true
                onClicked: {
                    preBtn.checked  = true
                    bNext = false
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

    Connections{
        target: popupTitle
        onPopupClose:  close()
    }

    Connections{
        target: InterAction
        onSigSetDevAddEnable:{
            if(next)
            {

            }
        }
    }

    //添加个数和单位

    Row{
        id:addRow
        width: parent.width
        height: 50
        anchors.top: maxDevInput.bottom
        anchors.topMargin: 50
        anchors.left: addDevText.left
        spacing: 250

        Item {
            width: devNumText.width +20 + devNumInput.width
            height: parent.height

            Text {
                id:devNumText
                text: qsTr("请输入添加设备数：")
                font.pixelSize: 20
                font.family: fontName
                color: "#FEFEFE"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }

            CusInputBox{
                id:devNumInput
                width: 100
                height: 50
                anchors.right: parent.right
                validator: RegExpValidator{regExp: /^([1-9]|[1-9]\d|1\d{2}|200)$/}
            }

            //提示
            Text {
                id:devNumTip
                text: qsTr("(最大设备数200,多个设备请分批次添加)")
                font.pixelSize: 12
                font.family: fontName
                color: "red"
                anchors.left: devNumInput.right
                anchors.leftMargin: 15
                anchors.bottom: devNumText.bottom
            }
        }

        Item {
            width: devWidthText.width +20 + devWidthInput.width
            height: parent.height
            Text {
                id:devWidthText
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("请输入设备宽度(mm)：")
                font.pixelSize: 20
                font.family: fontName
                color: "#FEFEFE"
            }

            CusInputBox{
                id:devWidthInput
                width: 100
                height: 50
                anchors.right: parent.right
                validator: RegExpValidator{regExp: /^(?:[1-9]|\d{2,3}|[1-4]\d{3}|5000)$./}
            }

        }
    }

    DevMagListview{
        id:devList
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top:addRow.bottom
        anchors.topMargin: 30
    }

    //清除按钮
    Button {
        id: clearBtn
        width: 60
        height: 30
        text: "清除"
        anchors.verticalCenter: devList.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 120
        font.family: fontName
        onClicked: {
            InterAction.delAllDevInfo()
            //设备数清零
            devNum = 0
        }
    }

    background: Rectangle{
        anchors.fill: parent
        color: "#061215"

    }

    //添加设备确认后关闭弹窗
    Timer{
        id:closeTimer
        interval: 2500
        running: false
        repeat: false
        onTriggered: {
            deviceMag.close()
        }
    }

    //底部矩形
    Rectangle
    {
        id : confirmRect
        color: "#212222"
        width: 1000
        height: 50
        anchors.bottom: parent.bottom

        //确定按钮
        CircleBtn{
            id: btnOk
            width: 120
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 300
            btnName: qsTr("确定")
            bPriority: true
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    //添加设备之前获取一次设备数量
                    devNum = InterAction.getDevNum()
                    if(Number(devNumInput.text) > 0&& Number(devWidthInput.text) > 0  )
                    {
                        //如果是逆序添加
                        if(!bNext)
                        {
                            console.log("see see devNum" + devNum)
                            //添加设备个数不能大于最大设备号
                            if(Number(devNumInput.text) > Number(maxDevInput.text))
                            {
                                devNumTip.text = "添加设备数不能大于最大设备数!"
                                return
                            }
                            //添加总个数不能大于最大设备号
                            if(devNum >= Number(maxDevInput.text))
                            {
                                devNumTip.text = "添加设备数已满！"
                                return
                            }
                        }

                        InterAction.setDevAddType(bNext)
                        InterAction.addDevINfo(bNext,Number(devNumInput.text),Number(devWidthInput.text),Number(maxDevInput.text))
                        //添加完设备后获取设备数量
                        devNum = InterAction.getDevNum()
                        //closeTimer.start()
                    }
                }
                onEntered: {
                    btnOk.press();
                }
                onExited: {
                    btnOk.release();
                }
            }
        }

        //取消按钮
        CircleBtn{
            id: btnCancel
            width: 120
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 300
            btnName: qsTr("取消")
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    deviceMag.close()

                }
                onEntered: {
                    btnCancel.press();
                }
                onExited: {
                    btnCancel.release();
                }
            }
        }

    }

}
