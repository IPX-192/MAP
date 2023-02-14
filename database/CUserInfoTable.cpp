#include "CUserInfoTable.h"

CUserInfoTable::CUserInfoTable(MapSysDatabase *dataBase)
{
    m_pDatabase = dataBase;
}

CUserInfoTable::~CUserInfoTable()
{
    if(m_pDatabase != nullptr)
    {
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

bool CUserInfoTable::Check_Config_Table()
{
    return true;
}
