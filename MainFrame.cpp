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

//    CUserInfoTable* pPersonnelTable = CDatabaseManage::GetInstance()->getPersonnelInfoTable();

//    if(nullptr == pPersonnelTable)
//    {
//        return bFlag;
//    }

//    bFlag = pPersonnelTable->queryAll(vTester);

    return bFlag;
}

bool MainFrame::insert(const CUserInfo &user)
{
    bool bFlag = false;
    return bFlag;
}

bool MainFrame::insert(const vector<CUserInfo> &vUser)
{
    bool bFlag = false;
    return bFlag;
}

bool MainFrame::isExist(const string &strID, const string &tagID)
{
    bool bFlag = false;
    return bFlag;
}

bool MainFrame::delUserByUserID(const string &strID)
{
    bool bFlag = false;
    return bFlag;
}

bool MainFrame::getMapOriginConfig(CMapOriginInfo &info)
{
    bool bFlag = false;
    return bFlag;
}

bool MainFrame::saveMapOriginConfig(const CMapOriginInfo &info)
{

}

