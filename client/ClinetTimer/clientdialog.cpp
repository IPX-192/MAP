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
#include<QRandomGenerator>

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
    //m_iplineedit->setText("127.0.0.1");
    m_iplineedit->setText("192.168.0.105");
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
    m_sendbutton = new QPushButton("发送11个");
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
    //layout7
    m_sendmessagetextedit = new QTextEdit;
    m_sendmessagetextedit->setFixedHeight(50);
    m_sendbutton2 = new QPushButton("发送4个");
    m_sendbutton2->setFixedHeight(50);
    QHBoxLayout *qhboxlayout7 = new QHBoxLayout;
    qhboxlayout7->addWidget(m_sendmessagetextedit);
    qhboxlayout7->addWidget(m_sendbutton2);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(qhboxlayout1,1);
    mainlayout->addLayout(qhboxlayout2,0.5);
    mainlayout->addLayout(qhboxlayout3,1);
    mainlayout->addLayout(qhboxlayout4,0.5);
    mainlayout->addLayout(qhboxlayout5,3);
    mainlayout->addLayout(qhboxlayout6,1);
    mainlayout->addLayout(qhboxlayout7,1);
    setLayout(mainlayout);
    setWindowTitle("Websocket Client");

    connect(m_linkbutton,SIGNAL(clicked(bool)),this,SLOT(connectToServer()));
    connect(m_disconnectbutton,SIGNAL(clicked(bool)),this,SLOT(stopClicked()));
    //connect(m_sendbutton,SIGNAL(clicked(bool)),this,SLOT(onSendButtonClicked2()));
    connect(m_clean,SIGNAL(clicked(bool)),this,SLOT(onCleanButtonClicked()));
    connect(&m_websocket,SIGNAL(connected()),this,SLOT(onconnected()));
    connect(&m_websocket,SIGNAL(disconnected()),this,SLOT(closeConnection()));
    connect(&m_websocket,SIGNAL(textMessageReceived(QString)),this,SLOT(onTextMessageReceived(QString)));
    connect(&m_sendTimer,&QTimer::timeout,this,&ClientDialog::onSendButtonClicked);
    connect(&m_sendTimer2,&QTimer::timeout,this,&ClientDialog::onSendButtonClicked2);
    // connect(m_sendbutton2,&QPushButton::clicked,this,&ClientDialog::onSendButtonClicked);
    connect(m_sendbutton,&QPushButton::clicked,&m_sendTimer,[=](){
        //m_sendTimer->start(300);
        if(m_sendTimer.isActive()){
            m_sendTimer.stop();
            m_sendbutton->setText("发送11个");
            flag=0;
            flag1=0;
        }
        else {
            m_sendTimer.start(300);
            m_sendbutton->setText("停止");
        }
    });
    connect(m_sendbutton2,&QPushButton::clicked,&m_sendTimer2,[=](){
        if(m_sendTimer2.isActive()){
            m_sendTimer2.stop();
            m_sendbutton2->setText("发送4个");
            flag3=0;
            flag4=0;
        }
        else {
            m_sendTimer2.start(300);
            m_sendbutton2->setText("停止");
        }
    });


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
    item1.insert("TagId",1001);
    item1.insert("X",100 + flag);
    item1.insert("Y",9281-flag1);
    item1.insert("Z",3);
    item1.insert("StaticTime",111);
    item1.insert("MapId",11);
    item1.insert("Battery",80);
    array.append(item1);

    QJsonObject item2;
    item2.insert("TagId",1002);
    item2.insert("X",24151+flag);
    item2.insert("Y",13241 - flag1);
    item2.insert("Z",3);
    item2.insert("StaticTime",111);
    item2.insert("MapId",11);
    item2.insert("Battery",80);
    array.append(item2);

    //    QJsonObject item3;
    //    item3.insert("TagId",1003);
    //    item3.insert("X",14827+flag);
    //    item3.insert("Y",-13241 + flag1);
    //    item3.insert("Z",3);
    //    item3.insert("StaticTime",111);
    //    item3.insert("MapId",11);
    //    item3.insert("Battery",80);
    //    array.append(item3);

    //    QJsonObject item4;
    //    item4.insert("TagId",1004);
    //    item4.insert("X",20189+flag);
    //    item4.insert("Y",6601 + flag1);
    //    item4.insert("Z",3);
    //    item4.insert("StaticTime",111);
    //    item4.insert("MapId",11);
    //    item4.insert("Battery",80);
    //    array.append(item4);

    //    QJsonObject item5;
    //    item5.insert("TagId",1005);
    //    item5.insert("X",21052+flag);
    //    item5.insert("Y",14210 - flag1);
    //    item5.insert("Z",3);
    //    item5.insert("StaticTime",111);
    //    item5.insert("MapId",11);
    //    item5.insert("Battery",80);
    //    array.append(item5);

    //    QJsonObject item6;
    //    item6.insert("TagId",1006);
    //    item6.insert("X",100000+flag);
    //    item6.insert("Y",5512 - flag1);
    //    item6.insert("Z",3);
    //    item6.insert("StaticTime",111);
    //    item6.insert("MapId",11);
    //    item6.insert("Battery",80);
    //    array.append(item6);

    //    QJsonObject item7;
    //    item7.insert("TagId",1007);
    //    item7.insert("X",221415+flag);
    //    item7.insert("Y",3241 - flag1);
    //    item7.insert("Z",3);
    //    item7.insert("StaticTime",111);
    //    item7.insert("MapId",11);
    //    item7.insert("Battery",80);
    //    array.append(item7);

    //    QJsonObject item8;
    //    item8.insert("TagId",1008);
    //    item8.insert("X",44151+flag);
    //    item8.insert("Y",241 - flag1);
    //    item8.insert("Z",3);
    //    item8.insert("StaticTime",111);
    //    item8.insert("MapId",11);
    //    item8.insert("Battery",80);
    //    array.append(item8);

    //    QJsonObject item9;
    //    item9.insert("TagId",1009);
    //    item9.insert("X",331124+flag);
    //    item9.insert("Y",0 - flag1);
    //    item9.insert("Z",3);
    //    item9.insert("StaticTime",111);
    //    item9.insert("MapId",11);
    //    item9.insert("Battery",80);
    //    array.append(item9);

    //    QJsonObject item10;
    //    item10.insert("TagId",1010);
    //    item10.insert("X",31240+flag);
    //    item10.insert("Y",1241 - flag1);
    //    item10.insert("Z",3);
    //    item10.insert("StaticTime",111);
    //    item10.insert("MapId",11);
    //    item10.insert("Battery",80);
    //    array.append(item10);

    //    QJsonObject item11;
    //    item11.insert("TagId",1011);
    //    item11.insert("X",8192+flag);
    //    item11.insert("Y",812 - flag1);
    //    item11.insert("Z",3);
    //    item11.insert("StaticTime",111);
    //    item11.insert("MapId",11);
    //    item11.insert("Battery",80);
    //    array.append(item11);

    //    QJsonArray arr1[20];
    //    int j=1000;
    //    for(int i=0;i<arr1->size();i++){
    //        QJsonObject itemTemp;
    //        QRandomGenerator rand;
    //        int x=rand.bounded(0,40000);
    //        int y=rand.bounded(-2500,2500);
    //        itemTemp.insert("TagId",j);
    //        itemTemp.insert("X",x+flag);
    //        itemTemp.insert("Y",y-flag1);
    //        itemTemp.insert("Z",0);
    //        itemTemp.insert("StaticTime",111);
    //        itemTemp.insert("MapId",11);
    //        itemTemp.insert("Battery",80);
    //        arr1->append(itemTemp);
    //        j++;
    //    }

    //    if(flag<= 400000)
    //    {
    //        flag+=10000;
    //    }
    flag+=1000;

    flag1 += 100;

    if(flag<= 400000)
    {
        flag+=1000;
    }else{
        flag=0;
    }
    // flag3+=1000;
    if(flag1<=30000){
        flag1+=100;
    }else{
        flag1=0;
    }

    groupObj.insert("TagList",array);

    QJsonDocument document;
    document.setObject(groupObj);
    QByteArray array_byte = document.toJson(QJsonDocument::Compact);
    QString hdwHeartRate(array_byte);


    m_websocket.sendTextMessage(hdwHeartRate);
}

void ClientDialog::onSendButtonClicked2()
{
    QString msg= m_sendmessagetextedit->document()->toPlainText();

    QJsonObject groupObj;
    groupObj.insert("MsgType",2);

    QJsonArray array ;
    QJsonObject item1;
    item1.insert("TagId",1234);
    item1.insert("X",30000 + flag3);
    item1.insert("Y",2918-flag4);
    item1.insert("Z",3);
    item1.insert("StaticTime",111);
    item1.insert("MapId",11);
    item1.insert("Battery",80);
    array.append(item1);

    //    QJsonObject item2;
    //    item2.insert("TagId",1111);
    //    item2.insert("X",70000-flag3);
    //    item2.insert("Y",13242 - flag4);
    //    item2.insert("Z",3);
    //    item2.insert("StaticTime",111);
    //    item2.insert("MapId",11);
    //    item2.insert("Battery",80);
    //    array.append(item2);

    //    QJsonObject item3;
    //    item3.insert("TagId",1341);
    //    item3.insert("X",82712-flag3);
    //    item3.insert("Y",17132 - flag4);
    //    item3.insert("Z",3);
    //    item3.insert("StaticTime",111);
    //    item3.insert("MapId",11);
    //    item3.insert("Battery",80);
    //    array.append(item3);

    //    QJsonObject item4;
    //    item4.insert("TagId",1341);
    //    item4.insert("X",15273+flag4);
    //    item4.insert("Y",0 );
    //    item4.insert("Z",3);
    //    item4.insert("StaticTime",111);
    //    item4.insert("MapId",11);
    //    item4.insert("Battery",80);
    //    array.append(item4);

    if(flag3<= 400000)
    {
        flag3+=1000;
    }else{
        flag3=0;
    }
    // flag3+=1000;
    if(flag4<=30000){
        flag4+=100;
    }else{
        flag4=0;
    }

    // flag4 += 100;

    groupObj.insert("TagList",array);

    QJsonDocument document;
    document.setObject(groupObj);
    QByteArray array_byte = document.toJson(QJsonDocument::Compact);
    //    QString hdwHeartRate(array_byte);

    qDebug()<<"see see"<<array_byte;

    QString hdwHeartRate(array_byte);
    m_websocket.sendTextMessage(hdwHeartRate);

}

//void ClientDialog::onSendButtonClicked3()
//{
//    QString msg= m_sendmessagetextedit->document()->toPlainText();

//    QJsonObject groupObj;
//    groupObj.insert("MsgType",2);
//    QJsonArray arr1[20];
//    int j=1000;
//    for(int i=0;i<arr1->size();i++){
//        QJsonObject itemTemp;
//        QRandomGenerator rand;
//        int x=rand.bounded(0,40000);
//        int y=rand.bounded(-2500,2500);
//        itemTemp.insert("TagId",j);
//        itemTemp.insert("X",x+flag);
//        itemTemp.insert("Y",y-flag1);
//        itemTemp.insert("Z",0);
//        itemTemp.insert("StaticTime",111);
//        itemTemp.insert("MapId",11);
//        itemTemp.insert("Battery",80);
//        arr1->append(itemTemp);
//        j++;
//    }

////    if(flag<= 400000)
////    {
////        flag+=10000;
////    }
//    flag+=1000;

//    flag1 += 100;

//    if(flag<= 400000)
//    {
//        flag+=1000;
//    }else{
//        flag=0;
//    }
//   // flag3+=1000;
//    if(flag1<=30000){
//        flag1+=100;
//    }else{
//        flag1=0;
//    }

//    groupObj.insert("TagList",*arr1);

//    QJsonDocument document;
//    document.setObject(groupObj);
//    QByteArray array_byte = document.toJson(QJsonDocument::Compact);
//    //    QString hdwHeartRate(array_byte);

//    //qDebug()<<"see see"<<jsString;

//    m_websocket.sendBinaryMessage(array_byte);

//}
//清除内容
void ClientDialog::onCleanButtonClicked()
{
    m_receivemessageTextEdit->clear();
}
