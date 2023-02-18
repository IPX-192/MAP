#include "CVersionInfoTable.h"
#include <QDebug>

CVersionInfoTable::CVersionInfoTable(MapSysDatabase *dataBase)
{
    m_pDatabase = dataBase;
}

CVersionInfoTable::~CVersionInfoTable()
{
    if(m_pDatabase != nullptr)
    {
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

bool CVersionInfoTable::Check_Config_Table()
{
    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    //如果不存在记录，则创建一条记录
    unsigned long long iCount = select<ProductInfoTable>(*m_pDatabase).count();

    if (iCount == 0)
    {
        ProductInfoTable info(*m_pDatabase);
        info.strSoftVersion = "1";
        info.update();
    }
    else
    {
        //如果记录存在，则暂时不做任何处理
    }

    bSuccess = true;

    return bSuccess;
}

string CVersionInfoTable::getVersionInfo()
{
    lock();

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return "";
    }

    vector<ProductInfoTable> vecSearch;

    vecSearch = select<ProductInfoTable>(*m_pDatabase).all();

    //存在数据则更新
    if(vecSearch.size() > 0)
    {
        auto &element = vecSearch[0];

        return element.strSoftVersion;
    }

    unlock();

    return "";
}

bool CVersionInfoTable::updateVersionInfo(const QString &info)
{
    lock();

    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    vector<ProductInfoTable> vecSearch;

    vecSearch = select<ProductInfoTable>(*m_pDatabase).all();

    //存在数据则更新
    if(vecSearch.size() > 0)
    {
        auto &element = vecSearch[0];
        element.strSoftVersion = info.toStdString();
        element.update();
    }
    //不存在数据则添加
    else
    {

    }

    bSuccess = true;

    unlock();

    return bSuccess;
}
