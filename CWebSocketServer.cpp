#include "CWebSocketServer.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMap>
#include <QBitmap>


CWebSocketServer::CWebSocketServer()
{
    m_WebSocketServer=new QWebSocketServer("server",QWebSocketServer::NonSecureMode);
    m_WebSocketServer->setMaxPendingConnections(20);

    connect(m_WebSocketServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));

    startServer();
}

CWebSocketServer::~CWebSocketServer()
{

}

void CWebSocketServer::startServer()
{

    //开始服务
    int i_port = 8195;
    m_WebSocketServer->listen(QHostAddress::Any,i_port);

}

void CWebSocketServer::stopServer()
{
    m_WebSocketServer->close();
}

//连接成功
void CWebSocketServer::onNewConnection()
{

    qDebug() << "hello";
    pSocket = m_WebSocketServer->nextPendingConnection();

    connect(pSocket,SIGNAL(textMessageReceived(QString)),this,SLOT(processTextMessage(QString)));
    connect(pSocket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));

}

//连接断开
void CWebSocketServer::socketDisconnected()
{

}


//数据是JSON格式，解析后判断是基站相关还是标签卡相关
void CWebSocketServer::processTextMessage(QString message)
{
    //qDebug()<<message;

    QJsonObject groupObj;

    QByteArray jsonBa = message.toLatin1();

    QJsonDocument m_document;

    QJsonParseError error;
    m_document = QJsonDocument::fromJson(jsonBa, &error);


    //解析JSON对象组合JSON数组
    if (m_document.isObject()) {
        groupObj = m_document.object();
        emit sendMeg( groupObj.value(0).toString());

    }

    if (groupObj.contains("AncList")) {
        QJsonArray array = groupObj.value("AncList").toArray();
        qDebug() << array[0].toString();
        qDebug() << array[1].toString();
        qDebug() << array[2].toString();
    }




}
