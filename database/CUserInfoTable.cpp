#include "CUserInfoTable.h"
#include <QDebug>

CUserInfoTable::CUserInfoTable(MapSysDatabase *dataBase)
{
    m_pDatabase = dataBase;
}

CUserInfoTable::~CUserInfoTable()
{
    if(m_pDatabase != nullptr)
    {
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

bool CUserInfoTable::Check_Config_Table()
{
    return true;
}

bool CUserInfoTable::addUserInfo(const CUserInfo &info)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    try
    {
        //判断新的名字是否可用
        if(!checkUserIDExist(info.strUserID(), info.itagID()))
        {
            bSuccess = true;

            UserInfoTable account(*m_pDatabase);
            account.strUserID = info.strUserID();
            account.strUserName = info.strUsername();
            account.strDepartment = info.strDepartment();
            account.strRole       = info.strRole();
            account.itagID = info.itagID();
            account.update();
        }
    }
    catch(Except e)
    {

    }

    unlock();

    return bSuccess;
}

bool CUserInfoTable::delUserInfo(const CUserInfo &info, bool bDeleteAll)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    try
    {
        if(bDeleteAll)
        {
            vector<UserInfoTable> vecSearch;

            m_pDatabase->begin();

            vecSearch = select<UserInfoTable>(*m_pDatabase).all();
            for(auto &element : vecSearch)
            {
                element.del();
            }

            m_pDatabase->commit();
        }
        else
        {
            string strUserID = info.strUserID();

            auto cursor = select<UserInfoTable>(*m_pDatabase, UserInfoTable::StrUserID == strUserID).cursor();

            if(cursor.rowsLeft())
            {
                bSuccess = true;

                UserInfoTable account(*m_pDatabase);
                account = (*cursor);

                account.del();
            }
        }
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

bool CUserInfoTable::updateUserInfo(const string userID, const CUserInfo &info)
{
    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    lock();

    bool bSuccess = false;

    try
    {
        bSuccess = true;

        auto cursor = select<UserInfoTable>(*m_pDatabase).cursor();
        UserInfoTable account(*m_pDatabase);
        if(cursor.rowsLeft())
        {
            account = (*cursor);
            account.strUserName = info.strUsername();
            account.strDepartment = info.strDepartment();
            account.strRole = info.strRole();
            account.itagID = info.itagID();
            account.update();
        }
        else
        {
            account.strUserName = info.strUsername();
            account.strDepartment = info.strDepartment();
            account.strRole = info.strRole();
            account.itagID = info.itagID();
            account.update();
        }
    }
    catch (Except e)
    {

    }

    unlock();

    return bSuccess;

}

bool CUserInfoTable::getAllUserInfo(vector<CUserInfo> &vecUsers)
{
    lock();

    bool bSuccess = true;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    m_pDatabase->begin();

    try
    {
        auto cursor = select<UserInfoTable>(*m_pDatabase).cursor();

        //存在则获取
        UserInfoTable account(*m_pDatabase);
        for (;cursor.rowsLeft(); cursor++)
        {
            account = (*cursor);

            CUserInfo test;
            test.setStrUserID(account.strUserID);
            test.setStrUsername(account.strUserName);
            test.setStrDepartment(account.strDepartment);
            test.setStrRole(account.strRole);
            test.setItagID(account.itagID);

            vecUsers.push_back(test);
        }
    }
    catch(Except e)
    {
        bSuccess = false;
    }

    m_pDatabase->commit();

    unlock();

    return bSuccess;
}

bool CUserInfoTable::getUserInfoByID(const string &strUserID, CUserInfo &info)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    try
    {
        auto cursor = select<UserInfoTable>(*m_pDatabase, UserInfoTable::StrUserID == strUserID).cursor();

        if(cursor.rowsLeft())
        {
            UserInfoTable account(*m_pDatabase);

            bSuccess = true;
            info.setStrUserID(account.strUserID);
            info.setStrUsername(account.strUserName);
            info.setStrDepartment(account.strDepartment);
            info.setStrRole(account.strRole);
            info.setItagID(account.itagID);
        }
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

bool CUserInfoTable::checkUserIDExist(const string &strUserID, const int &tagID)
{
    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    bool bFlag = false;

    unsigned long long iCount = select<UserInfoTable>(*m_pDatabase, UserInfoTable::StrUserID == strUserID && UserInfoTable::ItagID == tagID).count();

    if(iCount != 0)
    {
        bFlag = true;
    }

    return bFlag;
}

