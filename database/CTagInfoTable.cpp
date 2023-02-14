#include "CTagInfoTable.h"

CTagInfoTable::CTagInfoTable(MapSysDatabase *dataBase)
{
    m_pDatabase = dataBase;
}

CTagInfoTable::~CTagInfoTable()
{
    if(m_pDatabase != nullptr)
    {
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

bool CTagInfoTable::Check_Config_Table()
{
    return true;
}
