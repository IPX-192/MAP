#include "Clientdialog.h"
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCore>
#include <QDebug>
#include <iostream>
#include <QJsonArray>
#include <QMap>
#include <QBitmap>

#if _MSC_VER >= 1600  //MSVC2015>1899,  MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif


//192.168.0.105
ClientDialog::ClientDialog(const QUrl &url,bool debug,QWidget *parent)
    : QWidget(parent),m_url(url),m_debug(debug)
{
    //layout1
    QLabel *iplabel = new QLabel("IP地址");
    m_iplineedit =new QLineEdit;
    m_iplineedit->setText("172.16.16.67");
    QLabel *portlabel =new QLabel("端口");
    m_portspinbox = new QSpinBox;
    m_portspinbox->setRange(0,65535);
    m_portspinbox->setValue(8195);
    m_linkbutton = new QPushButton("连接");
    m_disconnectbutton = new QPushButton("断开");
    pButtonGroup = new QButtonGroup();
    pButtonGroup->setExclusive(true);
    m_linkbutton->setCheckable(true);
    m_disconnectbutton->setCheckable(true);
    pButtonGroup->addButton(m_linkbutton,0);
    pButtonGroup->addButton(m_disconnectbutton,1);

    QHBoxLayout *qhboxlayout1 = new QHBoxLayout;
    qhboxlayout1->addWidget(iplabel);
    qhboxlayout1->addWidget(m_iplineedit);
    qhboxlayout1->addWidget(portlabel);
    qhboxlayout1->addWidget(m_portspinbox);
    qhboxlayout1->addWidget(m_linkbutton);
    qhboxlayout1->addWidget(m_disconnectbutton);

    //layout2
    QLabel *sendmessagelabel = new QLabel("发送消息");
    QHBoxLayout *qhboxlayout2 = new QHBoxLayout;
    qhboxlayout2->addWidget(sendmessagelabel);

    //layout3
    m_sendmessagetextedit = new QTextEdit;
    m_sendmessagetextedit->setFixedHeight(50);
    m_sendbutton = new QPushButton("发送");
    m_sendbutton->setFixedHeight(50);
    QHBoxLayout *qhboxlayout3 = new QHBoxLayout;
    qhboxlayout3->addWidget(m_sendmessagetextedit);
    qhboxlayout3->addWidget(m_sendbutton);

    //layout4
    QLabel *receivemessagelabel = new QLabel("接收消息");
    QHBoxLayout *qhboxlayout4 = new QHBoxLayout;
    qhboxlayout4->addWidget(receivemessagelabel);

    //layout5
    m_receivemessageTextEdit = new QTextEdit;
    QHBoxLayout *qhboxlayout5 = new QHBoxLayout;
    qhboxlayout5->addWidget(m_receivemessageTextEdit);
    m_receivemessageTextEdit->setReadOnly(true);

    //layout6
    statusLabel = new QLabel("连接状态");
    m_clean = new QPushButton("清除");
    QHBoxLayout *qhboxlayout6 = new QHBoxLayout;
    qhboxlayout6->addWidget(statusLabel);
    qhboxlayout6->addStretch();
    qhboxlayout6->addWidget(m_clean);
    //
    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(qhboxlayout1,1);
    mainlayout->addLayout(qhboxlayout2,0.5);
    mainlayout->addLayout(qhboxlayout3,1);
    mainlayout->addLayout(qhboxlayout4,0.5);
    mainlayout->addLayout(qhboxlayout5,3);
    mainlayout->addLayout(qhboxlayout6,1);
    setLayout(mainlayout);
    setWindowTitle("Websocket Client");

    connect(m_linkbutton,SIGNAL(clicked(bool)),this,SLOT(connectToServer()));
    connect(m_disconnectbutton,SIGNAL(clicked(bool)),this,SLOT(stopClicked()));
    connect(m_sendbutton,SIGNAL(clicked(bool)),this,SLOT(onSendButtonClicked()));
    connect(m_clean,SIGNAL(clicked(bool)),this,SLOT(onCleanButtonClicked()));
    connect(&m_websocket,SIGNAL(connected()),this,SLOT(onconnected()));
    connect(&m_websocket,SIGNAL(disconnected()),this,SLOT(closeConnection()));
    connect(&m_websocket,SIGNAL(textMessageReceived(QString)),this,SLOT(onTextMessageReceived(QString)));
    connect(&m_sendTimer,&QTimer::timeout,this,&ClientDialog::onSendButtonClicked);
}

ClientDialog::~ClientDialog()
{
    m_websocket.errorString();
    m_websocket.close();
}
//断开连接操作
void ClientDialog::closeConnection(){
    m_linkbutton->setEnabled(true);
    m_disconnectbutton->setEnabled(false);
    m_sendmessagetextedit->setEnabled(false);
    m_sendbutton->setEnabled(false);
    m_receivemessageTextEdit->setEnabled(false);
    m_clean->setEnabled(false);
    statusLabel->setText(tr("disconnected"));
}
//连接服务器
void ClientDialog::connectToServer()
{
    QString path = QString("ws://%1:%2").arg(m_iplineedit->text()).arg(m_portspinbox->text());
    QUrl url = QUrl(path);
    m_websocket.open(url);
}
//连接上之后
void ClientDialog::onconnected(){
    qDebug() << "hello word!";
    statusLabel->setText(tr("connected"));
    m_linkbutton->setEnabled(false);
    m_disconnectbutton->setEnabled(true);
    m_sendmessagetextedit->setEnabled(true);
    m_sendbutton->setEnabled(true);
    m_receivemessageTextEdit->setEnabled(true);
    m_clean->setEnabled(true);
    //m_sendTimer.start(1000);
}
//收到消息
void ClientDialog::onTextMessageReceived(const QString &message)
{
    QString time = current_date_time->currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    m_receivemessageTextEdit->setText(time + "\n" + message);
}
//断开
void ClientDialog::stopClicked()
{
    m_websocket.close();
}
//发送消息
void ClientDialog::onSendButtonClicked()
{
    QString msg= m_sendmessagetextedit->document()->toPlainText();

    QJsonObject groupObj;
    groupObj.insert("MsgType",2);

    QJsonArray array ;
    QJsonObject item1;
    item1.insert("TagId",55555);
    item1.insert("X",20000 + flag);
    item1.insert("Y",20000);
    item1.insert("Z",3);
    item1.insert("StaticTime",111);
    item1.insert("MapId",11);
    item1.insert("Battery",80);
    array.append(item1);

    QJsonObject item2;
    item2.insert("TagId",1111);
    item2.insert("X",70000);
    item2.insert("Y",30000);
    item2.insert("Z",3);
    item2.insert("StaticTime",111);
    item2.insert("MapId",11);
    item2.insert("Battery",80);
    array.append(item2);

    if(flag<= 40000)
    {
        flag+=10000;
    }

    groupObj.insert("TagList",array);

    QJsonDocument document;
    document.setObject(groupObj);
    QByteArray array_byte = document.toJson(QJsonDocument::Compact);
    //    QString hdwHeartRate(array_byte);

    //qDebug()<<"see see"<<jsString;

    m_websocket.sendBinaryMessage(array_byte);
}
//清除内容
void ClientDialog::onCleanButtonClicked()
{
    m_receivemessageTextEdit->clear();
}
