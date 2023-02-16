import QtQuick 2.0
import Qt.labs.platform 1.1


FileDialog {
    id: fileDialog

    property string fileDialog_Title       //文件框标题
    property bool   fileDialog_Visible     //文件框可见性，只有指定可见性，属性设置才有效
    property var    fileDialog_NameFilter  //文件框过滤器

    signal  getFileString(var path);
    signal  closeFileDialog();

    title: fileDialog_Title

    nameFilters: fileDialog_NameFilter
    acceptLabel: qsTr("确定")
    rejectLabel: qsTr("取消")

    visible: fileDialog_Visible
    onAccepted: {
        getFileString(file);
        closeFileDialog();
    }
    onRejected: {
        closeFileDialog();
    }
}
