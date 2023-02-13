#ifndef CUSERINFOTABLE_H
#define CUSERINFOTABLE_H

/*************************************************
  <类    名>    CUserInfoTable
  <功能描述>     用户信息数据表

  <作    者>    tcy
  <时    间>    2023-02-13
**************************************************/

#include "CAbstractConfigInfo.h"

class CUserInfoTable : public CAbstractConfigInfo
{
public:
    CUserInfoTable(MapSysDatabase *dataBase);
    ~CUserInfoTable();

    virtual bool Check_Config_Table();

private:
    MapSysDatabase *m_pDatabase{nullptr};
};


#endif // CUSERINFOTABLE_H
