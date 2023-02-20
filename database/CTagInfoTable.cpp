#include "CTagInfoTable.h"
#include <QDebug>

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

//添加标签信息
bool CTagInfoTable::addTagInfo(const CTagInfo &info)
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
        if(checkTagIDAvailability(info.iTagID()))
        {
            bSuccess = true;

            TagInfoTable tag(*m_pDatabase);
            tag.iTagID = info.iTagID();
            tag.iMapID = info.iMapID();
            tag.iBattery = info.iBattery();
            tag.iPosX    = info.iPosX();
            tag.iPosY    = info.iPosY();
            tag.iPosZ    = info.iPosZ();
            tag.iStaticTime    = info.iStaticTime();
            tag.update();
        }
    }
    catch(Except e)
    {

    }

    unlock();

    return bSuccess;
}

//删除标签信息
bool CTagInfoTable::delTagInfo(const CTagInfo &info, bool bDeleteAll)
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
            vector<TagInfoTable> vecSearch;

            m_pDatabase->begin();

            vecSearch = select<TagInfoTable>(*m_pDatabase).all();
            for(auto &element : vecSearch)
            {
                element.del();
            }

            m_pDatabase->commit();
        }
        else
        {
            int tagInfoID = info.iTagID();

            //根据标签ID删除对象
            auto cursor = select<TagInfoTable>(*m_pDatabase, TagInfoTable::ITagID == tagInfoID).cursor();

            if(cursor.rowsLeft())
            {
                bSuccess = true;

                TagInfoTable tag(*m_pDatabase);
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

//更新标签信息
bool CTagInfoTable::updateTagInfo(const int &tagID, const CTagInfo &info)
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

        auto cursor = select<TagInfoTable>(*m_pDatabase, TagInfoTable::ITagID == tagID).cursor();

        if(cursor.rowsLeft())
        {
            TagInfoTable tag(*m_pDatabase);
            tag = *cursor;

            bSuccess = true;
            tag.iTagID = info.iTagID();
            tag.iMapID = info.iMapID();
            tag.iBattery = info.iBattery();
            tag.iPosX    = info.iPosX();
            tag.iPosY    = info.iPosY();
            tag.iPosZ    = info.iPosZ();
            tag.iStaticTime    = info.iStaticTime();
            tag.update();
        }

    }
    catch (Except e)
    {

    }

    unlock();

    return bSuccess;
}

//查找所有标签信息
bool CTagInfoTable::getAllTagInfo(vector<CTagInfo> &vecTags)
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
        auto cursor = select<TagInfoTable>(*m_pDatabase).cursor();

        //存在则获取
        TagInfoTable tag(*m_pDatabase);
        for (;cursor.rowsLeft(); cursor++)
        {
            tag = (*cursor);

            CTagInfo test;
            test.setITagID(tag.iTagID);
            test.setIMapID(tag.iMapID);
            test.setIBattery(tag.iBattery);
            test.setIPosX(tag.iPosX);
            test.setIPosY(tag.iPosY);
            test.setIPosZ(tag.iPosZ);
            test.setIStaticTime(tag.iStaticTime);

            vecTags.push_back(test);
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
bool CTagInfoTable::getTagInfoByID(const int &tagID, CTagInfo &info)
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
        auto cursor = select<TagInfoTable>(*m_pDatabase, TagInfoTable::ITagID == tagID).cursor();

        if(cursor.rowsLeft())
        {
            TagInfoTable tag(*m_pDatabase);
            tag = *cursor;

            bSuccess = true;
            info.setITagID(tag.iTagID);
            info.setIMapID(tag.iMapID);
            info.setIBattery(tag.iBattery);
            info.setIPosX(tag.iPosX);
            info.setIPosY(tag.iPosY);
            info.setIPosZ(tag.iPosZ);
            info.setIStaticTime(tag.iStaticTime);
        }
    }
    catch(Except e)
    {
    }

    unlock();

    return bSuccess;
}

//检查标签id是否存在
bool CTagInfoTable::checkTagIDAvailability(const int &tagID)
{
    bool bFlag = true;

    if(m_pDatabase == nullptr)
    {
        qDebug()<<"m_pDatabase == nullptr";
        return false;
    }

    unsigned long long iCount = select<TagInfoTable>(*m_pDatabase, TagInfoTable::ITagID == tagID).count();

    if(iCount != 0)
    {
        bFlag = false;
    }

    return bFlag;
}
