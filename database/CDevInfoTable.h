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

    //批量添加标签信息
    bool addDevInfo(const vector<CDevInfo> &vecInfo);

    //删除标签信息
    bool delDevInfo();

    //获取所有标签信息
    bool getAllDevInfo(vector<CDevInfo> &vecInfo);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CDEVINFOTABLE_H
