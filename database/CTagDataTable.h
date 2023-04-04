#ifndef CHISTORDATATABLE_H
#define CHISTORDATATABLE_H

#include "CAbstractConfigInfo.h"
#include "../datamanager/CTagData.h"

#define PER_PAGE_COUNT 11
//历史数据表
class CTagDataTable : public CAbstractConfigInfo
{
public:
    CTagDataTable(MapSysDatabase *dataBase);
    ~CTagDataTable();

    //初始化表格配置
    virtual bool Check_Config_Table();

    //添加历史数据
    bool addHistoryData(const CTagData &info);

    //删除历史数据
    bool delHistoryData(const CTagData &info, bool bDeleteAll = false);

    //获取所有标签信息
    bool getAllHistoryData(vector<CTagData> &vecDatas);

    //根据条件查找历史数据
    bool getHistoryDataByCondition(const string &strCondition, vector<CTagData> &vecDatas);

    //查询指定范围标签数据
    bool getPageHistoryData(vector<CTagData> &vecDatas, int &page);

    //获取所有数据count
    int getAllDataCount();

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CHISTORDATATABLE_H
