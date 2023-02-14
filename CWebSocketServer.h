#ifndef CWEBSOCKETSERVER_H
#define CWEBSOCKETSERVER_H

#include <QObject>
#include <QQmlContext>
#include <QString>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
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

    Q_INVOKABLE void test1();

protected:
    //获取IP地址
    QString getLocalIP();


signals:
    void sendMeg(QString meg);

    Q_INVOKABLE void setCurCoord(int coordX,int coordY);


private:

    //解析标签卡数组
    void parseLabelMeg(QJsonArray &array);

private slots:
    void onNewConnection();
    void socketDisconnected();
    void processTextMessage(QString message);
    void processByteArrayMessage(QByteArray array);


private:
    QWebSocketServer * m_WebSocketServer;
    QList<QWebSocket *> m_clients;
    QWebSocket *pSocket;
};

#endif // CWEBSOCKETSERVER_H
