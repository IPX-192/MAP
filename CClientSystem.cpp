#include "CClientSystem.h"

CClientSystem::CClientSystem()
{
    connect(&m_websocket,SIGNAL(connected()),this,SLOT(onconnected()));
    connect(&m_websocket,SIGNAL(textMessageReceived(QString)),this,SLOT(onTextMessageReceived(QString)));
}

CClientSystem::~CClientSystem()
{

}

//连接服务器
void CClientSystem::connectToServer(QString ip, QString com)
{
    QString path = QString("ws://%1:%2").arg(ip).arg(com);
    QUrl url = QUrl(path);
    m_websocket.open(url);
}

void CClientSystem::stopConnect()
{
    m_websocket.close();
}

void CClientSystem::sendMeg(QByteArray array)
{
    m_websocket.sendBinaryMessage(array);
}

//连接上之后
void CClientSystem::onconnected()
{

}

void CClientSystem::onTextMessageReceived(const QString &message)
{

}

