#ifndef CUSERINFOTABLE_H
#define CUSERINFOTABLE_H


#include "CAbstractConfigInfo.h"
#include "../datamanager/CUserInfo.h"

class CUserInfoTable : public CAbstractConfigInfo
{
public:
    CUserInfoTable(MapSysDatabase *dataBase);
    ~CUserInfoTable();

    virtual bool Check_Config_Table();

    bool addUserInfo(const CUserInfo &info);
    bool delUserInfo(const CUserInfo &info, bool bDeleteAll = false);
    bool updateUserInfo(const string userID, const CUserInfo &info);
    bool getAllUserInfo(vector<CUserInfo> &vecUsers);
    bool getUserInfoByID(const string &strUserID, CUserInfo &info);

    //判断账号是否可用
    bool checkUserIDAvailability(const string &strUserID, const int &tagID);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};


#endif // CUSERINFOTABLE_H
