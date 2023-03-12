#ifndef CCLIENTSYSTEM_H
#define CCLIENTSYSTEM_H

#include <QObject>

#include <QtWebSockets/QWebSocket>

class CClientSystem : public QObject
{
    Q_OBJECT
public:
    CClientSystem();
    ~CClientSystem();

public:
    void connectToServer(QString ip,QString com);
    //断开连接
    void stopConnect();
    //发送消息
    void sendMeg(QByteArray array);

public slots:
    void onconnected();
    void onTextMessageReceived(const QString &message);

private:
    QWebSocket m_websocket;
};

#endif // CCLIENTSYSTEM_H
