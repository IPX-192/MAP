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

//添加人员信息
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

//删除人员信息
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
        //删除所有信息
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
            //根据用户ID删除信息
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

//更新人员信息
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

//获取全部人员信息
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

//根据ID查找用户信息
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
            UserInfoTable account(*m_pDatabase) ;
            account = (*cursor);

            bSuccess = true;
            info.setStrUsername(account.strUserName);
            info.setStrDepartment(account.strDepartment);
            info.setStrRole(account.strRole);
            info.setItagID(account.itagID);
            info.setStrUserID(account.strUserID);
        }
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

//根据标签ID获取用户信息
bool CUserInfoTable::getUserInfoByTagID(const int &tagID, CUserInfo &info)
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
        auto cursor = select<UserInfoTable>(*m_pDatabase, UserInfoTable::ItagID == tagID).cursor();

        if(cursor.rowsLeft())
        {
            UserInfoTable account(*m_pDatabase) ;
            account = (*cursor);

            bSuccess = true;
            info.setStrUsername(account.strUserName);
            info.setStrDepartment(account.strDepartment);
            info.setStrRole(account.strRole);
            info.setStrUserID(account.strUserID);
            info.setItagID(account.itagID);
        }
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

//检查用户信息是否重叠，用户ID和标签ID不能重复
bool CUserInfoTable::checkUserIDExist(const string &strUserID, const int &tagID)
{
    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    bool bFlag = false;

    unsigned long long iCount = select<UserInfoTable>(*m_pDatabase, UserInfoTable::StrUserID == strUserID || UserInfoTable::ItagID == tagID).count();

    if(iCount != 0)
    {
        bFlag = true;
    }

    return bFlag;
}

