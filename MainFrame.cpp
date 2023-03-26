#include "MainFrame.h"
#include <QMap>
#include <QFileInfo>
#include <QGuiApplication>
#include <QHostAddress>
#include <QDir>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QBitmap>
#include <QFileInfoList>
#include <QDateTime>

MainFrame::MainFrame(QObject *parent)
{
    initialize();
}

MainFrame::~MainFrame()
{

}

void MainFrame::contextToQml(QQmlApplicationEngine &engine)
{
    engine.rootContext()->setContextProperty( "InterAction", this );
    engine.rootContext()->setContextProperty( "SocketServer", &m_SocketServer );
    engine.rootContext()->setContextProperty( "UserInfoModel", &m_userDataModel );
    engine.rootContext()->setContextProperty( "OnlineTagModel", &m_onlineTagModel );
    engine.rootContext()->setContextProperty( "TagDataModel", &m_tagDataModel);
    engine.rootContext()->setContextProperty( "DevInfoModel", &m_devInfoModel);
}

void MainFrame::initialize()
{
    connect(&m_SocketServer,&CWebSocketServer::parseTagIdInfo,this,&MainFrame::porcOnlineTag);
    connect(&m_SocketServer,&CWebSocketServer::clearFromTagData,this,&MainFrame::onClearTagInfoFrom);
}

bool MainFrame::copyImageFile(QString image)
{
    //去掉file:///
    image = image.mid(8);
    //获取需要拷贝的文件名称
    QFileInfo info(image);

    //获取可执行文件目录
    QString appPath = qApp->applicationDirPath();
    //查询该目录下是否存在文件夹LogoFile，没有则创建
    QString LogoDir = appPath + "/MapImg";
    QDir dir(LogoDir);
    if(!dir.exists())
    {
        dir.mkdir(LogoDir);
    }

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString   current_date = current_date_time.toString("hhmmsszzz");

    LogoDir += "/";
    //将logo重新命名
    LogoDir += "map";
    QString m_suffix =  image.right(4);
    LogoDir += m_suffix;

    //清空目录(保留默认logo)
    dir.setFilter(QDir::Files);
    int fileCount = static_cast<int>(dir.count());
    for (int i = 0; i < fileCount; i++)
    {
        dir.remove(dir[i]);
    }

    if(!QFile::copy(image,LogoDir))
    {
        return false;
    }

    return  true;
}

bool MainFrame::isSaveImage()
{
    //获取可执行文件目录
    QString appPath = qApp->applicationDirPath();
    //查询该目录下是否存在文件夹LogoFile，没有则创建
    QString LogoDir = appPath + "/MapImg";
    QDir dir(LogoDir);
    if(!dir.exists())
    {
        dir.mkdir(LogoDir);
    }
    QFileInfoList list = dir.entryInfoList();
    return list.count() > 2 ? true : false;
}

QString MainFrame::getImagePath()
{
    QString path =  "file:///" + qApp->applicationDirPath() + "/MapImg/";

    QDir dir(path);
    if(!dir.exists())
    {
        dir.mkdir(path);
    }

    QString imgSuffix;
    //清空目录(保留默认logo)
    dir.setFilter(QDir::Files);
    int fileCount = static_cast<int>(dir.count());
    for (int i = 0; i < fileCount; i++)
    {
        if(dir[i].contains("map"))
        {
            imgSuffix = dir[i].right(4);
        }
    }
    path += "map" + imgSuffix;
    return path;
}

bool MainFrame::queryAll(vector<CUserInfo> &vUser)
{
    bool bFlag = false;

    CUserInfoTable* pPersonnelTable = CDatabaseManage::GetInstance()->pUserInfo();

    if(nullptr == pPersonnelTable)
    {
        return bFlag;
    }

    bFlag = pPersonnelTable->getAllUserInfo(vUser);

    return bFlag;
}

bool MainFrame::insert(QString name, QString userID, QString depart, QString role, QString tagID)
{
    bool bFlag = false;

    CUserInfo user;
    user.setStrUsername(name.toStdString());
    user.setStrUserID(userID.toStdString());
    user.setStrDepartment(depart.toStdString());
    user.setStrRole(role.toStdString());
    user.setItagID(tagID.toInt());

    CTagInfo tag;
    tag.setITagID(tagID.toInt());

    CUserInfoTable* pPersonnelTable = CDatabaseManage::GetInstance()->pUserInfo();

    CTagInfoTable* pTagInfoTable = CDatabaseManage::GetInstance()->pTagInfo();

    if(nullptr == pPersonnelTable)
    {
        return bFlag;
    }

    //保证必须有部门
    if(user.strUserID() == "")
    {
        return bFlag;
    }

    if(user.itagID() == -1)
    {
        return bFlag;
    }

    if(!pPersonnelTable->checkUserIDExist(user.strUserID(), user.itagID()))
    {
        bFlag = pPersonnelTable->addUserInfo(user);
        bFlag = pTagInfoTable->addTagInfo(tag);
    }

    return bFlag;
}

bool MainFrame::isExist( QString strID, QString tagID )
{
    bool bFlag = false;

    CUserInfoTable* pPersonnelTable = CDatabaseManage::GetInstance()->pUserInfo();

    if(nullptr == pPersonnelTable)
    {
        return bFlag;
    }

    //保证必须有部门
    if(strID == "")
    {
        return bFlag;
    }

    if(tagID == -1)
    {
        return bFlag;
    }

    bFlag = pPersonnelTable->checkUserIDExist(strID.toStdString(), tagID.toInt());

    return bFlag;
}

bool MainFrame::loadAllUser()
{
    vector<CUserInfo> vUser;

    bool bSuccess = queryAll(vUser);

    if(bSuccess)
    {
        m_userDataModel.loadData(vUser);
    }

    return bSuccess;
}

bool MainFrame::delUserByUserID(QString strID)
{
    bool bFlag = false;

    CUserInfoTable* pPersonnelTable = CDatabaseManage::GetInstance()->pUserInfo();

    CTagInfoTable* pTagInfoTable = CDatabaseManage::GetInstance()->pTagInfo();

    if(nullptr == pTagInfoTable)
    {
        return bFlag;
    }

    if(nullptr == pPersonnelTable)
    {
        return bFlag;
    }

    CUserInfo info;
    info.setStrUserID(strID.toStdString());

    pPersonnelTable->getUserInfoByID(strID.toStdString(), info);

    CTagInfo tagInfo;
    tagInfo.setITagID(info.itagID());

    bFlag = pPersonnelTable->delUserInfo(info);

    bFlag = pTagInfoTable->delTagInfo(tagInfo);

    //刷新界面显示
    if(bFlag)
    {
        m_userDataModel.deleteRow(strID);
    }

    return bFlag;
}

bool MainFrame::loadAllTagData()
{
    bool bFlag = false;

    vector<CTagData> vecData;
    CTagDataTable* pTagDataTable = CDatabaseManage::GetInstance()->pTagData();

    if(nullptr == pTagDataTable)
    {
        return bFlag;
    }

    bFlag = pTagDataTable->getAllHistoryData(vecData);

    m_tagDataModel.loadData(vecData);
}

bool MainFrame::delTagData(QString dataID)
{
    bool bFlag = false;

    CTagDataTable* pTagDataTable = CDatabaseManage::GetInstance()->pTagData();


    if(nullptr == pTagDataTable)
    {
        return bFlag;
    }

    CTagData tagData;
    tagData.setIDataID(dataID.toInt());

    bFlag = pTagDataTable->delHistoryData(tagData);

    //刷新界面显示
    if(bFlag)
    {
        m_tagDataModel.deleteRow(dataID);
    }

    return bFlag;
}

bool MainFrame::delAllTagData()
{
    bool bFlag = false;

    CTagDataTable* pTagDataTable = CDatabaseManage::GetInstance()->pTagData();


    if(nullptr == pTagDataTable)
    {
        return bFlag;
    }

    CTagData tagData;
    bFlag = pTagDataTable->delHistoryData(tagData, true);

    //刷新界面显示
    if(bFlag)
    {
        m_tagDataModel.delAllData();
    }

    return bFlag;
}

bool MainFrame::delAllDevInfo()
{
    bool bFlag = false;

    CDevInfoTable* pDevInfoTable = CDatabaseManage::GetInstance()->pDevInfo();
    if(nullptr == pDevInfoTable)
    {
        return bFlag;
    }
    CDevInfo devinfo;
    bFlag = pDevInfoTable->delDevInfo(devinfo, true);

    //刷新界面显示
    if(bFlag)
    {
        m_devInfoModel.deleteAll();
    }
    //清除设备匹配
    m_SocketServer.clearDevMap();
    return bFlag;
}

bool MainFrame::addDevINfo(bool bRightOrder, int devNum, int devWidth,int maxDev)
{
    bool bFlag = false;
    if(devNum <= 0 || devWidth <= 0)
    {
        return bFlag;
    }

    //    if(m_devInfoModel.getMaxPos() >= 1000000)
    //    {
    //        return bFlag;
    //    }

    CDevInfoTable* pDevInfoTable = CDatabaseManage::GetInstance()->pDevInfo();
    if(nullptr == pDevInfoTable)
    {
        return bFlag;
    }

    //正序
    if(bRightOrder)
    {
        for(int i = 1; i<= devNum; i++)
        {
            int maxPos = m_devInfoModel.getMaxPos();
            int curDevID = m_devInfoModel.rowCount() + i;
            int curPos = maxPos + i*devWidth;

            if(curPos < 1000000)
            {
                CDevInfo info;
                info.setIDevID(curDevID);
                info.setStrDevName(QString::number(curDevID).toStdString());
                info.setIDevPos(curPos);
                info.setIDevWidth(devWidth);
                info.setBHighlight(false);
                bFlag = pDevInfoTable->addDevInfo(info);
            }
            else
            {
                return false;
            }
        }
    }
    //逆序添加的时候是最大设备号开始
    else
    {
        int startID = maxDev - m_devInfoModel.rowCount();

        for(int i = 0; i< devNum; i++)
        {
            int maxPos = m_devInfoModel.getMaxPos();
            int curDevID = startID - i;
            int curPos = maxPos + ( i + 1 )*devWidth;

            if(curPos < 1000000)
            {
                CDevInfo info;
                info.setIDevID(curDevID);
                info.setStrDevName(QString::number(curDevID).toStdString());
                info.setIDevPos(curPos);
                info.setIDevWidth(devWidth);
                info.setBHighlight(false);
                bFlag = pDevInfoTable->addDevInfo(info);
            }
            else
            {
                return false;
            }
        }
    }

    emit sigSetDevWidth(devWidth);
    loadDevINfo();
    updateBRightOrderConfig(bRightOrder);
    updateMaxNumConfig(maxDev);

    return true;
}

bool MainFrame::loadDevINfo()
{
    bool bFlag = false;

    vector<CDevInfo> vDevInfo;
    CDevInfoTable* pDevInfoTable = CDatabaseManage::GetInstance()->pDevInfo();

    if(nullptr == pDevInfoTable)
    {
        return bFlag;
    }

    bFlag = pDevInfoTable->getAllDevInfo(vDevInfo);

    m_devInfoModel.loadData(vDevInfo);

    return bFlag;
}

void MainFrame::bResetTimerACtive(bool bActive)
{
    m_devInfoModel.setTimerState(bActive);
}

bool MainFrame::bDevRightOrder()
{
    bool bFlag = true;

    CDevInfoConfig* pDevInfoConfig = CDatabaseManage::GetInstance()->pDevConfig();

    if(nullptr == pDevInfoConfig)
    {
        return bFlag;
    }

    bFlag = pDevInfoConfig->getDevInfoOrderConfig();

    return bFlag;
}

int MainFrame::getDevMaxNum()
{
    bool bFlag = true;

    CDevInfoConfig* pDevInfoConfig = CDatabaseManage::GetInstance()->pDevConfig();

    if(nullptr == pDevInfoConfig)
    {
        return bFlag;
    }

    bFlag = pDevInfoConfig->getDevInfoOrderConfig();

    return bFlag;
}

void MainFrame::updateBRightOrderConfig(bool bRightOrder)
{

    CDevInfoConfig* pDevInfoConfig = CDatabaseManage::GetInstance()->pDevConfig();

    if(nullptr == pDevInfoConfig)
    {
        return ;
    }

    pDevInfoConfig->updateOrderConfig(bRightOrder);
}

void MainFrame::updateMaxNumConfig(int maxnum)
{
    CDevInfoConfig* pDevInfoConfig = CDatabaseManage::GetInstance()->pDevConfig();

    if(nullptr == pDevInfoConfig)
    {
        return ;
    }

    pDevInfoConfig->updateMaxDevNumConfig(maxnum);
}

void MainFrame::setDevAddType(bool type)
{
    m_devAddNext = type;
}

bool MainFrame::getDevAddType()
{
    return m_devAddNext;
}

int MainFrame::getDevNum()
{
    return m_devInfoModel.dataNum();
}

bool MainFrame::getMapOriginConfig(CMapOriginInfo &info)
{
    bool bFlag = false;

    CMapOriginConfig *pMapConfigTable = CDatabaseManage::GetInstance()->pConfigMapOrigin();

    if( pMapConfigTable == nullptr )
    {
        return bFlag;
    }

    bFlag = pMapConfigTable->getMapOriginConfig(info);

    return bFlag;
}

bool MainFrame::saveMapOriginConfig(const CMapOriginInfo &info)
{
    bool bFlag = false;

    CMapOriginConfig *pMapConfigTable = CDatabaseManage::GetInstance()->pConfigMapOrigin();

    if( pMapConfigTable == nullptr )
    {
        return bFlag;
    }

    bFlag = pMapConfigTable->updateMapOriginConfig(info);

    return bFlag;
}

bool MainFrame::addHistoryTagData(COnlineTagInfo &info)
{
    bool bFlag = false;

    if(info.iTagID() == -1)
    {
        return bFlag;
    }

    CTagData data;
    data.setITagID(info.iTagID());
    data.setIPosX(info.iPosX());
    data.setIPosY(info.iPosY());
    data.setIPosZ(info.iPosZ());
    data.setIMapID(info.iMapID());
    data.setStrRole(info.strRole());
    data.setStrUserID(info.strUserID());
    data.setIBattery(info.iBattery());
    data.setStrUsername(info.strUsername());
    data.setStrDepartment(info.strDepartment());

    //数据保存时间
    QDateTime date = QDateTime::currentDateTime();
    QString currentDateTimeStr = date.toString("MM-dd hh:mm:ss");
    data.setSaveTime(currentDateTimeStr.toStdString());

    CTagDataTable* pTagDataTable = CDatabaseManage::GetInstance()->pTagData();

    if(nullptr == pTagDataTable)
    {
        return bFlag;
    }

    bFlag = pTagDataTable->addHistoryData(data);

    return bFlag;
}

void MainFrame::porcOnlineTag(const CTagInfo &tag)
{
    COnlineTagInfo info;
    info.setIPosX(tag.iPosX());
    info.setIPosY(tag.iPosY());
    info.setIPosZ(tag.iPosZ());
    info.setIMapID(tag.iMapID());
    info.setITagID(tag.iTagID());
    info.setIBattery(tag.iBattery());
    info.setIStaticTime(tag.iStaticTime());

    //根据tagid查找人员信息
    CUserInfoTable* pPersonnelTable = CDatabaseManage::GetInstance()->pUserInfo();

    CUserInfo user;
    if(pPersonnelTable->getUserInfoByTagID(tag.iTagID(), user))
    {
        info.setStrUserID(user.strUserID());
        info.setStrDepartment(user.strDepartment());
        info.setStrRole(user.strRole());
        info.setStrUsername(user.strUsername());

        if(m_onlineTagModel.checkTagInfoUpdate(info))
        {
            m_onlineTagModel.addData(info);
            m_devInfoModel.updateDevStatus(info.iPosX());
            addHistoryTagData(info);
        }
        else
        {
            m_onlineTagModel.deleteRow(info.iTagID());
        }
    }
}

void MainFrame::onClearTagInfoFrom()
{
    qDebug()<<"响应清空表格";
    m_onlineTagModel.deleteAll();
}
