#ifndef CDEVINFOCONFIG_H
#define CDEVINFOCONFIG_H

#include "CAbstractConfigInfo.h"

//地图原点配置
class CDevInfoConfig : public CAbstractConfigInfo
{
public:
    CDevInfoConfig(MapSysDatabase *dataBase);
    ~CDevInfoConfig();

    //初始化表格配置
    virtual bool Check_Config_Table();

    //获取正序、逆序配置
    bool getDevInfoOrderConfig();

    //更新原点配置
    bool updateOrderConfig(const bool &bRightOrder);

    //获取最大设备数配置
    int getMaxDevNum();

    //更新最大设备数配置
    bool updateMaxDevNumConfig(const int &maxNum);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CDEVINFOCONFIG_H
