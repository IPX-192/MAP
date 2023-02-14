#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QNetworkConfigurationManager>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include "CWebSocketServer.h"

class MainFrame : public QObject
{
    Q_OBJECT
public:
    MainFrame(QObject *parent = nullptr);
    virtual ~MainFrame();

    /**
       * @brief 注册上下文属性到qml
       */
    void contextToQml(QQmlApplicationEngine &engine);

    void initialize();

public:
    //服务器对象
    CWebSocketServer         m_SocketServer;

};

#endif // MAINFRAME_H
