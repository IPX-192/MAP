#ifndef CUSERINFOTABLE_H
#define CUSERINFOTABLE_H

/*************************************************
  <类    名>    CUserInfoTable
  <功能描述>     用户信息数据表

  <作    者>    tcy
  <时    间>    2023-02-13
**************************************************/

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
    bool getAllUserInfo(const string userID, const CUserInfo &info);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};


#endif // CUSERINFOTABLE_H
