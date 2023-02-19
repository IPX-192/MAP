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
#include "./datamodel/COnlineTagModel.h"

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

    //获取地图原点配置
    bool getMapOriginConfig(CMapOriginInfo &info);

    //保存地图原点配置
    bool saveMapOriginConfig(const CMapOriginInfo &info);

    //添加人员
    Q_INVOKABLE bool insert(QString name, QString userID, QString depart, QString role, QString tagID);

    //检查是否重复添加
    Q_INVOKABLE bool isExist(QString strID, QString tagID);

    //加载所有人员信息
    Q_INVOKABLE bool loadAllUser();

    //删除指定人员
    Q_INVOKABLE bool delUserByUserID(QString strID);

public slots:

    //处理收到的标签信息
    void porcOnlineTag(const CTagInfo &tag);

    //清理实时的表格tag数据
    void onClearTagInfoFrom();

public:
    //服务器对象
    CWebSocketServer         m_SocketServer;

    //人员model
    CUserInfoModel m_userDataModel;

    //在线标签信息model
    COnlineTagInfoModel m_onlineTagModel;
};

#endif // MAINFRAME_H
