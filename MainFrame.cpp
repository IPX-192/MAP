#include "MainFrame.h"

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
}

void MainFrame::initialize()
{
    connect(&m_SocketServer,&CWebSocketServer::parseTagIdInfo,this,&MainFrame::porcOnlineTag);
    connect(&m_SocketServer,&CWebSocketServer::clearFromTagData,this,&MainFrame::onClearTagInfoFrom);
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

void MainFrame::setDevAddType(bool type)
{
    m_devAddNext = type;
}

bool MainFrame::getDevAddType()
{
    return m_devAddNext;
}

void MainFrame::addDev(int devNum, int devWidth)
{
    qDebug()<<"qqqqqqqqqqqqqqwww"<<devNum<<devWidth;
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

        m_onlineTagModel.addData(info);
    }
}

void MainFrame::onClearTagInfoFrom()
{
    m_onlineTagModel.deleteAll();
}

