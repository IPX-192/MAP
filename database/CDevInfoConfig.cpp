#include "CDevInfoConfig.h"
#include <QDebug>

CDevInfoConfig::CDevInfoConfig(MapSysDatabase *dataBase)
{
    m_pDatabase = dataBase;
}

CDevInfoConfig::~CDevInfoConfig()
{
    if(m_pDatabase != nullptr)
    {
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

bool CDevInfoConfig::Check_Config_Table()
{
    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    //如果不存在记录，则创建一条记录
    unsigned long long iCount = select<DevConfigTable>(*m_pDatabase).count();

    if (iCount == 0)
    {
        DevConfigTable config(*m_pDatabase);
        config.bRightOrder = true;
        config.maxDev = 0;
        config.update();
    }
    else
    {
        //如果记录存在，则暂时不做任何处理
    }

    bSuccess = true;

    return bSuccess;
}

bool CDevInfoConfig::getDevInfoOrderConfig()
{
    lock();

    bool bRightOrder = true;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bRightOrder;
    }

    vector<DevConfigTable> vecSearch;

    vecSearch = select<DevConfigTable>(*m_pDatabase).all();

    //存在数据则更新
    if(vecSearch.size() > 0)
    {
        auto &element = vecSearch[0];
        bRightOrder = element.bRightOrder;
    }

    unlock();

    return bRightOrder;
}

bool CDevInfoConfig::updateOrderConfig(const bool &bRightOrder)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    vector<DevConfigTable> vecSearch;

    vecSearch = select<DevConfigTable>(*m_pDatabase).all();

    //存在数据则更新
    if(vecSearch.size() > 0)
    {
        auto &element = vecSearch[0];
        element.bRightOrder  = bRightOrder;
        element.update();
    }

    bSuccess = true;

    unlock();

    return bSuccess;
}

int CDevInfoConfig::getMaxDevNum()
{
    lock();

    int maxDev = 0;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return maxDev;
    }

    vector<DevConfigTable> vecSearch;

    vecSearch = select<DevConfigTable>(*m_pDatabase).all();

    //存在数据则更新
    if(vecSearch.size() > 0)
    {
        auto &element = vecSearch[0];
        maxDev = element.maxDev;
    }

    unlock();

    return maxDev;
}

bool CDevInfoConfig::updateMaxDevNumConfig(const int &maxNum)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    vector<DevConfigTable> vecSearch;

    vecSearch = select<DevConfigTable>(*m_pDatabase).all();

    //存在数据则更新
    if(vecSearch.size() > 0)
    {
        auto &element = vecSearch[0];
        element.maxDev  = maxNum;
        element.update();
    }

    bSuccess = true;

    unlock();

    return bSuccess;
}
