#ifndef CTAGINFOTABLE_H
#define CTAGINFOTABLE_H

/*************************************************
  <类    名>    CTagInfoTable
  <功能描述>     标签信息数据表

  <作    者>    tcy
  <时    间>    2023-02-13
**************************************************/

#include "CAbstractConfigInfo.h"

class CTagInfoTable : public CAbstractConfigInfo
{
public:
    CTagInfoTable(MapSysDatabase *dataBase);
    ~CTagInfoTable();

    virtual bool Check_Config_Table();

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CTAGINFOTABLE_H
