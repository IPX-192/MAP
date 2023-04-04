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
        tag.saveTime = info.saveTime();
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

            bSuccess = true;

            m_pDatabase->commit();
        }
        else
        {
            int tagdataID = info.iDataID();

            //根据数据ID删除对象
            auto cursor = select<TagDataTable>(*m_pDatabase, TagDataTable::Id == tagdataID).cursor();

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
            test.setIDataID(tag.id);
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
            test.setSaveTime(tag.saveTime);
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
                                                               Like(TagDataTable::SaveTime,"%"+strCondition+"%") ||
                                                               Like(TagDataTable::StrDepartment,"%"+strCondition+"%")),
                             select<TagDataTable>(*m_pDatabase,Like(TagDataTable::IMapID,"%"+strCondition+"%"))).cursor();

        for(;cursor.rowsLeft();cursor++)
        {
            CTagData record;
            TagDataTable table(*m_pDatabase);
            table = *cursor;

            record.setIDataID(table.id);
            record.setITagID(table.iTagID);
            record.setIMapID(table.iMapID);
            record.setIBattery(table.iBattery);
            record.setIPosX(table.iPosX);
            record.setIPosY(table.iPosY);
            record.setIPosZ(table.iPosZ);
            record.setIStaticTime(table.iStaticTime);
            record.setStrUserID(table.strUserID);
            record.setStrRole(table.strRole);
            record.setStrUsername(table.strUserName);
            record.setSaveTime(table.saveTime);
            record.setStrDepartment(table.strDepartment);

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

bool CTagDataTable::getPageHistoryData(vector<CTagData> &vecDatas, int &page)
{
    lock();


    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    if(page < 1)
    {
        return bSuccess;
    }

    int startPage = PER_PAGE_COUNT * (page - 1);

    m_pDatabase->begin();

    try
    {
        QString query = QString("SELECT * FROM  TagDataTable_ LIMIT %1 OFFSET %2").arg(PER_PAGE_COUNT).arg(startPage);

        Records recods = m_pDatabase->query(query.toStdString());

        for (const Record& record : recods) {
            // 处理查询结果...
            CTagData tagData;
            tagData.setIDataID(atoi(record[0]));
            tagData.setITagID(atoi(record[2]));
            tagData.setSaveTime(record[4]);
            tagData.setIMapID(atoi(record[5]));
            tagData.setIBattery(atoi(record[6]));
            tagData.setIPosX(atoi(record[7]));
            tagData.setIPosY(atoi(record[8]));
            tagData.setIPosZ(atoi(record[9]));
            tagData.setIStaticTime(atoi(record[10]));
            tagData.setStrUserID(record[11]);
            tagData.setStrUsername(record[12]);
            tagData.setStrDepartment(record[13]);
            tagData.setStrRole(record[14]);

            vecDatas.push_back(tagData);
        }


        /*
        auto cursor = select<TagDataTable>(*m_pDatabase, TagDataTable::Id >= startPage && TagDataTable::Id < endPage).cursor();

        for(;cursor.rowsLeft();cursor++)
        {
            CTagData record;
            TagDataTable table(*m_pDatabase);
            table = *cursor;
            record.setIDataID(table.id);
            record.setITagID(table.iTagID);
            record.setIMapID(table.iMapID);
            record.setIBattery(table.iBattery);
            record.setIPosX(table.iPosX);
            record.setIPosY(table.iPosY);
            record.setIPosZ(table.iPosZ);
            record.setIStaticTime(table.iStaticTime);
            record.setStrUserID(table.strUserID);
            record.setStrRole(table.strRole);
            record.setStrUsername(table.strUserName);
            record.setSaveTime(table.saveTime);
            record.setStrDepartment(table.strDepartment);

            vecDatas.push_back(record);
        }
        */
    }
    catch(Except e)
    {
        bSuccess = false;
    }

    m_pDatabase->commit();

    unlock();

    return bSuccess;
}

int CTagDataTable::getAllDataCount()
{
    lock();

    int count = 0;
    bool bSuccess = false;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return bSuccess;
    }

    m_pDatabase->begin();

    try
    {
       count = int(select<TagDataTable>(*m_pDatabase).all().size());
    }

    catch(Except e)
    {
        bSuccess = false;
    }

    m_pDatabase->commit();

    unlock();

    return count;
}
