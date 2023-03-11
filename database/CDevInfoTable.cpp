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

//添加标签信息
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
        //判断新的ID是否可用
        bSuccess = true;

        DevInfoTable Dev(*m_pDatabase);
        Dev.iDevID = info.iDevID();
        Dev.devName = info.strDevName();
        Dev.devPos = info.iDevPos();
        Dev.update();
    }
    catch(Except e)
    {

    }

    unlock();

    return bSuccess;
}

//删除标签信息
bool CDevInfoTable::delDevInfo(const CDevInfo &info, bool bDeleteAll)
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
        if(bDeleteAll)
        {
            vector<DevInfoTable> vecSearch;

            m_pDatabase->begin();

            vecSearch = select<DevInfoTable>(*m_pDatabase).all();
            for(auto &element : vecSearch)
            {
                element.del();
            }

            m_pDatabase->commit();
        }
        else
        {
            int DevInfoID = info.iDevID();

            //根据标签ID删除对象
            auto cursor = select<DevInfoTable>(*m_pDatabase, DevInfoTable::IDevID == DevInfoID).cursor();

            if(cursor.rowsLeft())
            {
                bSuccess = true;

                DevInfoTable Dev(*m_pDatabase);
                Dev = (*cursor);

                Dev.del();
            }
        }
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

//更新标签信息
bool CDevInfoTable::updateDevInfo(const int &DevID, const CDevInfo &info)
{
    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    lock();

    bool bSuccess = false;

    try
    {
        bSuccess = true;

        auto cursor = select<DevInfoTable>(*m_pDatabase, DevInfoTable::IDevID == DevID).cursor();

        if(cursor.rowsLeft())
        {
            DevInfoTable Dev(*m_pDatabase);
            Dev = *cursor;

            bSuccess = true;
            Dev.iDevID = info.iDevID();
            Dev.devName = info.strDevName();
            Dev.devPos = info.iDevPos();
            Dev.update();
        }

    }
    catch (Except e)
    {

    }

    unlock();

    return bSuccess;
}

//查找所有标签信息
bool CDevInfoTable::getAllDevInfo(vector<CDevInfo> &vecDevs)
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
        DevInfoTable Dev(*m_pDatabase);
        for (;cursor.rowsLeft(); cursor++)
        {
            Dev = (*cursor);

            CDevInfo test;
            test.setIDevID(Dev.iDevID);
            test.setStrDevName(Dev.devName);
            test.setIDevPos(Dev.devPos);

            vecDevs.push_back(test);
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

//根据id获取标签对象
bool CDevInfoTable::getDevInfoByID(const int &DevID, CDevInfo &info)
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
        auto cursor = select<DevInfoTable>(*m_pDatabase, DevInfoTable::IDevID == DevID).cursor();

        if(cursor.rowsLeft())
        {
            DevInfoTable Dev(*m_pDatabase);
            Dev = *cursor;

            bSuccess = true;
            info.setIDevID(Dev.iDevID);
            info.setStrDevName(Dev.devName);
            info.setIDevPos(Dev.devPos);
        }
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

//检查标签id是否存在
bool CDevInfoTable::checkDevIDAvailability(const int &DevID)
{
    bool bFlag = true;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    unsigned long long iCount = select<DevInfoTable>(*m_pDatabase, DevInfoTable::IDevID == DevID).count();

    if(iCount != 0)
    {
        bFlag = false;
    }

    return bFlag;
}
