#include "CMapOriginConfig.h"

CMapOriginConfig::CMapOriginConfig(MapSysDatabase *dataBase)
{
    m_pDatabase = dataBase;
}

CMapOriginConfig::~CMapOriginConfig()
{
    if(m_pDatabase != nullptr)
    {
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

bool CMapOriginConfig::Check_Config_Table()
{
    bool bSuccess = false;

    //如果不存在记录，则创建一条记录
    unsigned long long iCount = select<MapOriginConfig>(*m_pDatabase).count();

    if (iCount == 0)
    {
        MapOriginConfig orignPos(*m_pDatabase);
        orignPos.iPosX = 0;
        orignPos.iPosY = 0;
        orignPos.iPosX = 0;
        orignPos.update();
    }
    else
    {
        //如果记录存在，则暂时不做任何处理
    }

    bSuccess = true;

    return bSuccess;
}
