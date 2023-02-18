#include "MainFrame.h"

MainFrame::MainFrame(QObject *parent)
{

}

MainFrame::~MainFrame()
{

}

void MainFrame::contextToQml(QQmlApplicationEngine &engine)
{
    engine.rootContext()->setContextProperty( "InterAction", &m_SocketServer );
}

void MainFrame::initialize()
{

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

    CUserInfoTable* pPersonnelTable = CDatabaseManage::GetInstance()->pUserInfo();

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

    if(!pPersonnelTable->checkUserIDAvailability(user.strUserID(), user.itagID()))
    {
        bFlag = pPersonnelTable->addUserInfo(user);
    }

    return bFlag;
}

bool MainFrame::isExist(const string &strID, const int &tagID)
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

    bFlag = pPersonnelTable->checkUserIDAvailability(strID, tagID);

    return bFlag;
}

bool MainFrame::delUserByUserID(const string &strID)
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
    info.setStrUserID(strID);

    pPersonnelTable->getUserInfoByID(strID, info);

    CTagInfo tagInfo;
    tagInfo.setITagID(info.itagID());

    bFlag = pPersonnelTable->delUserInfo(info);

    bFlag = pTagInfoTable->delTagInfo(tagInfo);

    return bFlag;
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

