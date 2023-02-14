#ifndef CTAGINFOTABLE_H
#define CTAGINFOTABLE_H


#include "CAbstractConfigInfo.h"

class CTagInfoTable : public CAbstractConfigInfo
{
public:
    CTagInfoTable(MapSysDatabase *dataBase);
    ~CTagInfoTable();

    virtual bool Check_Config_Table();

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CTAGINFOTABLE_H
