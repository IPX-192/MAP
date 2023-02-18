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
#include "./database/CDatabaseManage.h"
#include "./datamodel/CUserInfoModel.h"

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

    //删除指定人员
    bool delUserByUserID(const string& strID);

    //获取地图原点配置
    bool getMapOriginConfig(CMapOriginInfo &info);

    //保存地图原点配置
    bool saveMapOriginConfig(const CMapOriginInfo &info);

    //添加人员
    Q_INVOKABLE bool insert(QString name, QString userID, QString depart, QString role, QString tagID);

    //检查是否重复添加
    Q_INVOKABLE bool isExist(QString &strID, QString &tagID);

    //加载所有人员信息
    Q_INVOKABLE bool loadAllUser();

public:
    //服务器对象
    CWebSocketServer         m_SocketServer;

    //人员model
    CUserInfoModel m_userDataModel;


};

#endif // MAINFRAME_H
