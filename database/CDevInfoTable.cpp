#include "CDevInfoTable.h"
#include <QDebug>

CDevInfoTable::CDevInfoTable(MapSysDatabase *dataBase)
{
    m_pDatabase = dataBase;
}

CDevInfoTable::~CDevInfoTable()
{
    if(m_pDatabase != nullptr)
    {
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

bool CDevInfoTable::Check_Config_Table()
{
    return true;
}

bool CDevInfoTable::addDevInfo(const CDevInfo &info)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    try
    {
        bSuccess = true;

        DevInfoTable tag(*m_pDatabase);
        tag.iDevID = info.iDevID();
        tag.devName = info.strDevName();
        tag.devPos = info.iDevPos();
        tag.update();
    }
    catch(Except e)
    {

    }

    unlock();

    return bSuccess;
}

bool CDevInfoTable::addDevInfo(const vector<CDevInfo> &vecInfo)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    try
    {
        bSuccess = true;

        for(auto info : vecInfo)
        {
            DevInfoTable tag(*m_pDatabase);
            tag.iDevID = info.iDevID();
            tag.devName = info.strDevName();
            tag.devPos = info.iDevPos();
            tag.update();
        }
    }
    catch(Except e)
    {

    }

    unlock();

    return bSuccess;
}

bool CDevInfoTable::delDevInfo()
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    try
    {
        //删除所有标签信息
        vector<DevInfoTable> vecSearch;

        m_pDatabase->begin();

        vecSearch = select<DevInfoTable>(*m_pDatabase).all();
        for(auto &element : vecSearch)
        {
            element.del();
        }

        m_pDatabase->commit();
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

bool CDevInfoTable::getAllDevInfo(vector<CDevInfo> &vecInfo)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    m_pDatabase->begin();

    try
    {
        auto cursor = select<DevInfoTable>(*m_pDatabase).cursor();

        //存在则获取
        DevInfoTable tag(*m_pDatabase);
        for (;cursor.rowsLeft(); cursor++)
        {
            tag = (*cursor);

            CDevInfo info;
            info.setIDevID(info.iDevID());
            info.setIDevPos(info.iDevPos());
            info.setStrDevName(info.strDevName());

            vecInfo.push_back(info);
        }

        bSuccess = true;
    }
    catch(Except e)
    {
        bSuccess = false;
    }

    m_pDatabase->commit();

    unlock();

    return bSuccess;
}
