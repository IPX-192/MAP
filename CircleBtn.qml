import QtQuick 2.0


Item {
    id:root

    property string btnColor:"#0E4F8C"
    property int btnHeight: 48

    property string bdColorNoClick: "#666666"       //非激活状态边框颜色
    property string bdColorNormal: "#1ADDFC"        //激活状态边框颜色
    property string bdColorPriority: "#05A9C3"      //优先状态边框颜色
    property string btnColorHighLight: "#065A59"    //高亮状态
    property string btnColorNormal:  "#123464"      //激活状态按钮颜色
    property string btnColorClicked: "#1649B4"      //点击状态按钮颜色
    property string btnColorSelected: "#0A6E82"     //选中状态按钮颜色
    property string textColorNoClick: "#666666"     //非激活状态文本颜色
    property string textColorNormal: "#FFFFFF"      //激活状态文本颜色
    property string textColorClick: "#EEEEEE"       //点击状态文本颜色
    property bool bEnable: true                     //是否激活
    property bool bPress: false                     //是否点击
    property bool bHighlight: false                 //是否高亮
    property bool bPriority: false                  //按钮优先级
    property bool bSelected: false                  //是否被选中
    property bool isImageBtn: false                 //是否是图片按钮

    property string btnName: qsTr("Button")         //按钮名称
    property int fontSize: 20                       //按钮文本大小
    property int imageTextInterval: 35              //图片按钮文本间隔
    property string imagePath:""

    width: 140
    height: 48
    signal   clicked()                //鼠标点击事件信号
    signal   pressed()
    signal   released()

    function  press()
    {
        bPress = true;
        updateBtnStatus();
    }

    function release()
    {
        bPress = false;
        updateBtnStatus();
    }

    function updateBtnStatus()
    {
        if(bEnable)
        {
            if(bHighlight)
            {
                btnRect.color = btnColorHighLight;
                btnRect.border.color = btnRect.color;
                btnText.color = textColorClick;
            }
            else
            {
                btnRect.color = btnColorNormal;
                btnRect.border.color = bdColorNormal;
                btnText.color = textColorNormal;
            }

            if(bPriority)
            {
                btnRect.border.color = bdColorPriority;
            }

            if(bSelected)
            {
                btnRect.color = btnColorSelected;
                btnRect.border.color = btnRect.color;
                btnText.color = textColorClick;
            }

            if(bPress)
            {
                btnRect.color = btnColorClicked;
                btnRect.border.color = btnRect.color;
                btnText.color = textColorClick;
            }

        }
        else
        {
            btnRect.color = btnColorNormal;
            btnRect.border.color = bdColorNoClick;
            btnText.color = textColorNoClick;
        }
    }

    Component.onCompleted: {
        updateBtnStatus();
    }

    Rectangle {
        id: btnRect
        anchors.fill:parent
        radius: 24
        color: btnColorNormal
        border.color: bdColorNormal
    }

    Text {
        id: btnText
        visible: isImageBtn ? false :true
        anchors.centerIn: parent
        font{family: fontName; pixelSize: fontSize}
        font.bold: bSelected
        color: textColorNormal
        text: btnName
    }

    Image {
        anchors.right: bImagetnText.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        source: imagePath
    }

    Text {
        id: bImagetnText
        visible: isImageBtn ? true :false
        anchors.right: parent.right
        anchors.rightMargin:imageTextInterval
        anchors.verticalCenter: parent.verticalCenter
        font{family: fontName; pixelSize: fontSize}
        font.bold: bSelected
        color: textColorNormal
        text: btnName
    }

    MouseArea
    {
        anchors.fill: parent
        onEntered: {
            root.press()
        }
        onExited: {
            root.release()
        }
        onClicked: {
            root.clicked()
        }
    }
}
