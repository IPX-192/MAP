#ifndef CMAPORIGINCONFIG_H
#define CMAPORIGINCONFIG_H

/*************************************************
  <类    名>    CMapOriginConfig
  <功能描述>     地图原点配置

  <作    者>    tcy
  <时    间>    2023-02-13
**************************************************/

#include "CAbstractConfigInfo.h"

class CMapOriginConfig : public CAbstractConfigInfo
{
public:
    CMapOriginConfig(MapSysDatabase *dataBase);
    ~CMapOriginConfig();

    virtual bool Check_Config_Table();

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CMAPORIGINCONFIG_H
