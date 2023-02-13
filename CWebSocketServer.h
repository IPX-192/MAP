#ifndef CWEBSOCKETSERVER_H
#define CWEBSOCKETSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

#include <QTime>

#if _MSC_VER >= 1600  //MSVC2015>1899,  MSVC_VER=14.0
#pragma execution_character_set("utf-8")
#endif


class CWebSocketServer : public QObject
{
    Q_OBJECT
public:
    CWebSocketServer();
    ~CWebSocketServer();

public:
    //开始服务
    void startServer();

    //停止服务
    void stopServer();

signals:
    void sendMeg(QString meg);

private slots:
    void onNewConnection();
    void socketDisconnected();
    void processTextMessage(QString message);


private:
    QWebSocketServer * m_WebSocketServer;
    QList<QWebSocket *> m_clients;
    QWebSocket *pSocket;
};

#endif // CWEBSOCKETSERVER_H
