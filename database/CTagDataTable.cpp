#include "CTagDataTable.h"
#include <QDebug>

CTagDataTable::CTagDataTable(MapSysDatabase *dataBase)
{
    m_pDatabase = dataBase;
}

CTagDataTable::~CTagDataTable()
{
    if(m_pDatabase != nullptr)
    {
        delete m_pDatabase;
        m_pDatabase = nullptr;
    }
}

bool CTagDataTable::Check_Config_Table()
{
    return true;
}

bool CTagDataTable::addHistoryData(const CTagData &info)
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

        TagDataTable tag(*m_pDatabase);
        tag.iDataID = info.iDataID();
        tag.iTagID = info.iTagID();
        tag.iMapID = info.iMapID();
        tag.iBattery = info.iBattery();
        tag.iPosX    = info.iPosX();
        tag.iPosY    = info.iPosY();
        tag.iPosZ    = info.iPosZ();
        tag.iStaticTime = info.iStaticTime();
        tag.strUserName = info.strUsername();
        tag.strUserID = info.strUserID();
        tag.strDepartment = info.strDepartment();
        tag.strRole = info.strRole();
        tag.update();
    }
    catch(Except e)
    {

    }

    unlock();

    return bSuccess;
}

bool CTagDataTable::delHistoryData(const CTagData &info, bool bDeleteAll)
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
            vector<TagDataTable> vecSearch;

            m_pDatabase->begin();

            vecSearch = select<TagDataTable>(*m_pDatabase).all();
            for(auto &element : vecSearch)
            {
                element.del();
            }

            m_pDatabase->commit();
        }
        else
        {
            int tagdataID = info.iDataID();

            //根据数据ID删除对象
            auto cursor = select<TagDataTable>(*m_pDatabase, TagDataTable::IDataID == tagdataID).cursor();

            if(cursor.rowsLeft())
            {
                bSuccess = true;

                TagDataTable tag(*m_pDatabase);
                tag = (*cursor);

                tag.del();
            }
        }
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

bool CTagDataTable::getAllHistoryData(vector<CTagData> &vecDatas)
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
        auto cursor = select<TagDataTable>(*m_pDatabase).cursor();

        //存在则获取
        TagDataTable tag(*m_pDatabase);
        for (;cursor.rowsLeft(); cursor++)
        {
            tag = (*cursor);

            CTagData test;
            test.setIDataID(tag.iDataID);
            test.setITagID(tag.iTagID);
            test.setIMapID(tag.iMapID);
            test.setIBattery(tag.iBattery);
            test.setIPosX(tag.iPosX);
            test.setIPosY(tag.iPosY);
            test.setIPosZ(tag.iPosZ);
            test.setIStaticTime(tag.iStaticTime);
            test.setStrUserID(tag.strUserID);
            test.setStrRole(tag.strRole);
            test.setStrUsername(tag.strUserName);
            test.setStrDepartment(tag.strDepartment);

            vecDatas.push_back(test);
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

bool CTagDataTable::getHistoryDataByCondition(const string &strCondition, vector<CTagData> &vecDatas)
{
    lock();

    bool bRes = true;

    m_pDatabase->begin();

    try
    {
        auto cursor = union_(select<TagDataTable>(*m_pDatabase,Like(TagDataTable::ITagID,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::IBattery,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::IPosX,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::IPosY,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::IPosZ,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::IStaticTime,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::StrUserID,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::StrRole,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::StrUserName,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::StrDepartment,"%"+strCondition+"%")),
                             select<TagDataTable>(*m_pDatabase,Like(TagDataTable::IMapID,"%"+strCondition+"%"))).cursor();

        for(;cursor.rowsLeft();cursor++)
        {
            CTagData record;
            TagDataTable table(*m_pDatabase);
            table = *cursor;

            vecDatas.push_back(record);
        }
    }
    catch(Except e)
    {
        bRes = false;
    }

    m_pDatabase->commit();

    unlock();

    return bRes;
}
