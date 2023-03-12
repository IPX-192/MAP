#include "serverdialog.h"
#include "ui_serverdialog.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QDebug>
#include <QByteArray>


#if _MSC_VER >= 1600  //MSVC2015>1899,  MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif


ServerDialog::ServerDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    //qhboxLayout1部分代码
    QLabel* monitorLabel= new QLabel("监听端口");
    m_monitorSpinBox = new QSpinBox();
    m_monitorSpinBox->setRange(0,65535);
    m_monitorSpinBox->setValue(8000);
    m_startButton = new QPushButton("启动服务");
    m_stopButton = new QPushButton("停止服务");
    m_stopButton->setEnabled(false);
    QHBoxLayout *qhboxLayout1 = new QHBoxLayout;
    qhboxLayout1->addWidget(monitorLabel);
    qhboxLayout1->addWidget(m_monitorSpinBox);
    qhboxLayout1->addWidget(m_startButton);
    qhboxLayout1->addWidget(m_stopButton);

    //qhboxLayout2部分代码
    QLabel* sendLabel=new QLabel("发送消息");
    QHBoxLayout *qhboxLayout2 = new QHBoxLayout;
    qhboxLayout2->addWidget(sendLabel);

    //qhboxLayout3部分代码
    m_sendTextedit = new QTextEdit;
    m_sendTextedit->setEnabled(false);
    m_sendTextedit->setFixedHeight(50);
    m_sendButton= new QPushButton("发送");
    m_sendButton->setEnabled(false);
    m_sendButton->setFixedHeight(50);

    QHBoxLayout *qhboxlayout3 = new QHBoxLayout;
    qhboxlayout3->addWidget(m_sendTextedit,2);
    qhboxlayout3->addWidget(m_sendButton,1);

    //qvboxlayout411
    QLabel* receiveLabel = new QLabel("接收消息");
    m_receiveTextEdit = new QTextEdit();
    m_receiveTextEdit->setReadOnly(true);

    QVBoxLayout *qvboxlayout411 = new QVBoxLayout;
    qvboxlayout411->addWidget(receiveLabel);
    qvboxlayout411->addWidget(m_receiveTextEdit);

    //qhboxlayout412
    m_cleanButton = new QPushButton("清除");
    m_cleanButton->setEnabled(false);
    QHBoxLayout *qhboxlayout412 = new QHBoxLayout;
    qhboxlayout412->addStretch();
    qhboxlayout412->addWidget(m_cleanButton);

    //qvboxlayout41
    QVBoxLayout *qvboxlayout41 = new QVBoxLayout;
    qvboxlayout41->addLayout(qvboxlayout411);
    qvboxlayout41->addLayout(qhboxlayout412);

    //qvboxlayout42
    QLabel* linkclientLabel=new QLabel("连接客户端");
    m_linkclientListWidget=new QListWidget;
    QVBoxLayout* qvboxlayout42 = new QVBoxLayout;
    qvboxlayout42->addWidget(linkclientLabel);
    qvboxlayout42->addWidget(m_linkclientListWidget);

    //qvboxlayout4
    QHBoxLayout *qhboxlayout4 = new QHBoxLayout;
    qhboxlayout4->addLayout(qvboxlayout41,2);
    qhboxlayout4->addLayout(qvboxlayout42,1);

    //mainlayout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(qhboxLayout1,1);
    mainLayout->addLayout(qhboxLayout2,0.5);
    mainLayout->addLayout(qhboxlayout3,1);
    mainLayout->addLayout(qhboxlayout4,3);

    this->setLayout(mainLayout);
    this->setWindowTitle("Websocket Server");

    m_WebSocketServer=new QWebSocketServer("server",QWebSocketServer::NonSecureMode);

    m_WebSocketServer->setMaxPendingConnections(10);
    connect(m_WebSocketServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
    connect(m_startButton,SIGNAL(clicked(bool)),this,SLOT(onStartButtonClick()));
    connect(m_stopButton,SIGNAL(clicked(bool)),this,SLOT(onStopButtonClick()));
    connect(m_cleanButton,SIGNAL(clicked(bool)),this,SLOT(onCleanButtonClick()));
    connect(m_sendButton,SIGNAL(clicked(bool)),this,SLOT(onSendButtonClick()));

}

ServerDialog::~ServerDialog()
{
    delete ui;
}

void ServerDialog::onStartButtonClick(){
    int i_port = m_monitorSpinBox->text().toInt();
    m_WebSocketServer->listen(QHostAddress::Any,i_port);
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
    qDebug()<<m_WebSocketServer->isListening();
    qDebug()<<m_WebSocketServer->serverPort();
    qDebug()<<m_WebSocketServer->serverAddress();
}
void ServerDialog::onStopButtonClick(){
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
    m_WebSocketServer->close();
}
void ServerDialog::onSendButtonClick(){
    QString msg = m_sendTextedit->document()->toPlainText();
    //    pSocket->sendTextMessage(msg);
    QList<QWebSocket *>::iterator i;
    for(i=m_clients.begin(); i!=m_clients.end(); ++i)
    {
        //          qDebug() << (*i);
        (*i)->sendTextMessage(msg);
    }
}
void ServerDialog::onCleanButtonClick(){
    m_receiveTextEdit->clear();
}
//连接上之后
void ServerDialog::onNewConnection(){

    qDebug() << "hello";
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
    m_sendTextedit->setEnabled(true);
    m_sendButton->setEnabled(true);
    m_cleanButton->setEnabled(true);

    pSocket = m_WebSocketServer->nextPendingConnection();

    connect(pSocket,SIGNAL(textMessageReceived(QString)),this,SLOT(processTextMessage(QString)));
    connect(pSocket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));

    QString item = pSocket->peerAddress().toString();
    m_linkclientListWidget->addItem(item);
    m_clients << pSocket;
}
//收到消息并显示
void ServerDialog::processTextMessage(QString message){
    QString time = current_date_time->currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QString item = pSocket->peerAddress().toString();
    m_receiveTextEdit->append(time +""+ item + "\n" + message);
}

//连接断开的操作
void ServerDialog::socketDisconnected(){
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
    m_sendButton->setEnabled(false);
    m_sendTextedit->setEnabled(false);
    m_receiveTextEdit->setEnabled(false);
    m_cleanButton->setEnabled(false);
}
