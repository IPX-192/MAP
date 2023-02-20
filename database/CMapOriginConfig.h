#ifndef CMAPORIGINCONFIG_H
#define CMAPORIGINCONFIG_H

#include "CAbstractConfigInfo.h"
#include "../datamanager/CMapOriginInfo.h"

//地图原点配置
class CMapOriginConfig : public CAbstractConfigInfo
{
public:
    CMapOriginConfig(MapSysDatabase *dataBase);
    ~CMapOriginConfig();

    //初始化表格配置
    virtual bool Check_Config_Table();

    //获取原点配置
    bool getMapOriginConfig(CMapOriginInfo &info);
    //更新原点配置
    bool updateMapOriginConfig(const CMapOriginInfo &info);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CMAPORIGINCONFIG_H
