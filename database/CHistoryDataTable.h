#ifndef CHISTORDATATABLE_H
#define CHISTORDATATABLE_H

#include "CAbstractConfigInfo.h"
#include "../datamanager/CHistoryData.h"

//历史数据表
class CHistoryDataTable : public CAbstractConfigInfo
{
public:
    CHistoryDataTable(MapSysDatabase *dataBase);
    ~CHistoryDataTable();

    //初始化表格配置
    virtual bool Check_Config_Table();

    //添加历史数据
    bool addHistoryData(const CHistoryData &info);

    //删除历史数据
    bool delHistoryData(const CHistoryData &info, bool bDeleteAll);

    //获取所有标签信息
    bool getAllHistoryData(vector<CHistoryData> &vecDatas);

    //根据条件查找历史数据
    bool getHistoryDataByCondition(const string &strCondition, vector<CHistoryData> &vecDatas);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CHISTORDATATABLE_H
