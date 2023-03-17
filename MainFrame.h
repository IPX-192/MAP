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
#include "./datamodel/CTagDataModel.h"
#include "./datamodel/CDevInfoModel.h"

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

    //缓存更改过的图片文件
    Q_INVOKABLE bool copyImageFile(QString image);
    //判断是否更改过背景图片
    Q_INVOKABLE bool isSaveImage();

    Q_INVOKABLE QString getImagePath();
    //查询所有添加人员
    bool queryAll(vector<CUserInfo>& vUser);

    //获取地图原点配置
    bool getMapOriginConfig(CMapOriginInfo &info);

    //保存地图原点配置
    bool saveMapOriginConfig(const CMapOriginInfo &info);

    //添加历史数据
    bool addHistoryTagData(COnlineTagInfo &info);

    //添加人员
    Q_INVOKABLE bool insert(QString name, QString userID, QString depart, QString role, QString tagID);

    //检查是否重复添加
    Q_INVOKABLE bool isExist(QString strID, QString tagID);

    //加载所有人员信息
    Q_INVOKABLE bool loadAllUser();

    //删除指定人员
    Q_INVOKABLE bool delUserByUserID(QString strID);

    //加载所有历史数据
    Q_INVOKABLE bool loadAllTagData();

    //删除指定历史数据
    Q_INVOKABLE bool delTagData(QString dataID);

    //删除所有设备
    Q_INVOKABLE bool delAllDevInfo();

    //添加设备
    Q_INVOKABLE bool addDevINfo(bool bRightOrder, int devNum, int devWidth,int maxDev);

    //加载所有设备
    Q_INVOKABLE bool loadDevINfo();

    //暂停刷新设备
    Q_INVOKABLE void bResetTimerACtive(bool bActive);

    //获取设备是否正序配置
    Q_INVOKABLE bool bDevRightOrder();

    //获取最大设备
    Q_INVOKABLE int getDevMaxNum();

    //更新设备值
    Q_INVOKABLE void updateBRightOrderConfig(bool bRightOrder);

    //更新最大设备数量
    Q_INVOKABLE void updateMaxNumConfig(int maxnum);

    //////设备管理相关///////
    Q_INVOKABLE void setDevAddType(bool type);

    Q_INVOKABLE bool getDevAddType();

    Q_INVOKABLE int  getDevNum();
signals:
    Q_INVOKABLE void sigSetDevAddEnable(bool next);

public slots:

    //处理收到的标签信息
    void porcOnlineTag(const CTagInfo &tag);

    //清理实时的表格tag数据
    void onClearTagInfoFrom();

public:
    //服务器对象
    CWebSocketServer    m_SocketServer;

    //人员model
    CUserInfoModel      m_userDataModel;

    //在线标签信息model
    COnlineTagInfoModel m_onlineTagModel;

    //历史数据model
    CTagDataModel       m_tagDataModel;

    //设备model
    CDevInfoModel       m_devInfoModel;

    //是否是正向添加设备
    bool                m_devAddNext{true};
};

#endif // MAINFRAME_H
