#ifndef CWEBSOCKETSERVER_H
#define CWEBSOCKETSERVER_H

#include <QObject>
#include <QQmlContext>
#include <QString>
#include <QTimer>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include "./datamanager/CTagInfo.h"

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
    Q_INVOKABLE void startServer(bool local);

    //停止服务
    Q_INVOKABLE void stopServer();


    //获取IP地址
    Q_INVOKABLE QString getLocalIP();

    Q_INVOKABLE bool getServerConnectStatus();


signals:
    void sendMeg(QString meg);

    void parseTagIdInfo(CTagInfo &tag);

    void clearFromTagData();

    Q_INVOKABLE void setCurCoord(int coordX,int coordY,int tagID);

    Q_INVOKABLE void sendCurServerAddress(QString address);

    Q_INVOKABLE void clearDrawCoord();


private:

    //解析标签卡数组
    void parseLabelMeg(QJsonArray &array);

    //解析标签卡数据(对象)
    void parseLabelMeg(QJsonObject &object);

private slots:
    void onNewConnection();
    void socketDisconnected();
    void processTextMessage(QString message);
    void processByteArrayMessage(QByteArray array);
    void onRecvDataFinish();


private:
    QWebSocketServer * m_WebSocketServer;
    QList<QWebSocket *> m_clients;
    QWebSocket *pSocket;
    QTimer     m_RecvTimer;
    bool       m_bConnectStatus{false};
};

#endif // CWEBSOCKETSERVER_H
