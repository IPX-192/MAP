#ifndef CDEVINFOTABLE_H
#define CDEVINFOTABLE_H

#include "CAbstractConfigInfo.h"
#include "../datamanager/CDevInfo.h"

//设备信息表
class CDevInfoTable : public CAbstractConfigInfo
{
public:
    CDevInfoTable(MapSysDatabase *dataBase);
    ~CDevInfoTable();

    //初始化表格配置
    virtual bool Check_Config_Table();

    //添加标签信息
    bool addDevInfo(const CDevInfo &info);

    //删除标签信息
    bool delDevInfo(const CDevInfo &info, bool bDeleteAll = false);

    //更新标签信息
    bool updateDevInfo(const int &DevID, const CDevInfo &info);

    //获取所有标签信息
    bool getAllDevInfo(vector<CDevInfo> &vecDevs);

    //根据ID查找标签信息
    bool getDevInfoByID(const int &DevID, CDevInfo &info);

    //判断标签是否可用
    bool checkDevIDAvailability(const int &DevID);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CDEVINFOTABLE_H
