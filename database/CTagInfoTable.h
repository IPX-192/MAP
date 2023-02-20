#ifndef CTAGINFOTABLE_H
#define CTAGINFOTABLE_H


#include "CAbstractConfigInfo.h"
#include "../datamanager/CTagInfo.h"

class CTagInfoTable : public CAbstractConfigInfo
{
public:
    CTagInfoTable(MapSysDatabase *dataBase);
    ~CTagInfoTable();

    //初始化表格配置
    virtual bool Check_Config_Table();

    //添加标签信息
    bool addTagInfo(const CTagInfo &info);

    //删除标签信息
    bool delTagInfo(const CTagInfo &info, bool bDeleteAll = false);

    //更新标签信息
    bool updateTagInfo(const int &tagID, const CTagInfo &info);

    //获取所有标签信息
    bool getAllTagInfo(vector<CTagInfo> &vecTags);

    //根据ID查找标签信息
    bool getTagInfoByID(const int &tagID, CTagInfo &info);

    //判断标签是否可用
    bool checkTagIDAvailability(const int &tagID);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CTAGINFOTABLE_H
