#ifndef CMAPORIGINCONFIG_H
#define CMAPORIGINCONFIG_H

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
