#include "CMapOriginConfig.h"
#include <QDebug>

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

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

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

bool CMapOriginConfig::getMapOriginConfig(CMapOriginInfo &info)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    vector<MapOriginConfig> vecSearch;

    vecSearch = select<MapOriginConfig>(*m_pDatabase).all();

    //存在数据则更新
    if(vecSearch.size() > 0)
    {
        auto &element = vecSearch[0];

        info.setIPosX(element.iPosX);
        info.setIPosY(element.iPosY);
        info.setIPosZ(element.iPosZ);

        bSuccess = true;
    }
    //不存在数据则添加
    else
    {
        bSuccess = false;
    }

    unlock();

    return bSuccess;
}

bool CMapOriginConfig::updateMapOriginConfig(const CMapOriginInfo &info)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    vector<MapOriginConfig> vecSearch;

    vecSearch = select<MapOriginConfig>(*m_pDatabase).all();

    //存在数据则更新
    if(vecSearch.size() > 0)
    {
        auto &element = vecSearch[0];
        element.iPosX  = info.iPosX();
        element.iPosY  = info.iPosY();
        element.iPosZ  = info.iPosZ();
        element.update();
    }
    //不存在数据则添加
    else
    {
        MapOriginConfig tester(*m_pDatabase);
        tester.iPosX  = info.iPosX();
        tester.iPosY  = info.iPosY();
        tester.iPosZ  = info.iPosZ();
        tester.update();
    }

    bSuccess = true;

    unlock();

    return bSuccess;
}
