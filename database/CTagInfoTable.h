#ifndef CTAGINFOTABLE_H
#define CTAGINFOTABLE_H


#include "CAbstractConfigInfo.h"
#include "../datamanager/CTagInfo.h"

class CTagInfoTable : public CAbstractConfigInfo
{
public:
    CTagInfoTable(MapSysDatabase *dataBase);
    ~CTagInfoTable();

    virtual bool Check_Config_Table();
    bool addTagInfo(const CTagInfo &info);
    bool delTagInfo(const CTagInfo &info, bool bDeleteAll = false);
    bool updateTagInfo(const int &tagID, const CTagInfo &info);
    bool getAllTagInfo(vector<CTagInfo> &vecTags);
    bool getTagInfoByID(const int &tagID, CTagInfo &info);

    //判断标签是否可用
    bool checkTagIDAvailability(const int &tagID);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CTAGINFOTABLE_H
