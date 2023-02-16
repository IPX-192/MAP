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
#include "./datamanager/CUserInfo.h"
#include "./datamanager/CMapOriginInfo.h"
#include "./datamanager/CTagInfo.h"

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

    //查询所有添加人员
    bool queryAll(vector<CUserInfo>& vUser);

    //添加人员
    bool insert(const CUserInfo& user);
    bool insert(const vector<CUserInfo>& vUser);

    //检查是否重复添加
    bool isExist(const string& strID, const string& tagID);

    //删除指定人员
    bool delUserByUserID(const string& strID);

    //获取地图原点配置
    bool getMapOriginConfig(CMapOriginInfo &info);

    //保存地图原点配置
    bool saveMapOriginConfig(const CMapOriginInfo &info);


public:
    //服务器对象
    CWebSocketServer         m_SocketServer;

};

#endif // MAINFRAME_H
