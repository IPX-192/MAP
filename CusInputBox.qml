import QtQuick 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.5


TextField {
    id:inputBox

    property int inputBoxWidth
    property int inputBoxheight
    property int textPointSize:16
    property bool inputBoxFocus:false
    property string  tipsString:qsTr("")        //提示性文字
    property string  tipsStringColor:qsTr("")   //提示性文字颜色
    property alias displayText: inputBox.text

    placeholderTextColor:"#EEEEEE"
    //focus: inputBoxFocus
    hoverEnabled: true
    selectionColor: "#292E38"
    selectedTextColor:"#999999"
    horizontalAlignment:TextInput.AlignHCenter
    placeholderText:tipsString
    focus: true


    font {
        family:fontName
        pixelSize:textPointSize
    }

    background: Rectangle {
        id:bcRect
        implicitWidth: inputBoxWidth
        implicitHeight: inputBoxheight
        color:"#070908"
        border.color: "#3D3E42"

    }
    color: "#F0F0F0"

    onPressed: {

    }

    onReleased: {

    }

    onTextEdited: {
        //console.log("正在输入")
    }

    onEditingFinished: {

    }

    onFocusChanged: {

    }

}
