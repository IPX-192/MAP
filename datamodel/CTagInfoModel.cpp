#include "CTagInfoModel.h"

CTagInfoModel::CTagInfoModel(QObject *parent)
{
    m_roleName.insert(TagIDRole, "tagID");
    m_roleName.insert(MapIDRole, "mapID");
    m_roleName.insert(BatteryRole, "battery");
    m_roleName.insert(PosXRole, "posX");
    m_roleName.insert(PosYRole, "posY");
    m_roleName.insert(PosZRole, "posZ");
    m_roleName.insert(StaticTimeRole, "staticTime");
}

//标签数据进行显示
void CTagInfoModel::loadData(const vector<CTagInfo> &vecTag)
{
    m_TagInfoData.clear();

    for(auto it : vecTag)
    {
        m_TagInfoData.push_front(it);
    }

    emit layoutChanged();
}

//标签表添加数据
void CTagInfoModel::addData(CTagInfo &info)
{
    m_TagInfoData.push_front(info);

    emit layoutChanged();
}

//标签信息
void CTagInfoModel::addData(vector<CTagInfo> &vecTag)
{
    for(auto it : vecTag)
    {
        m_TagInfoData.push_back(it);
    }
    emit layoutChanged();
}

//删除一行
void CTagInfoModel::deleteRow(int &rowIndex)
{
    if( rowIndex>=0 && rowIndex<m_TagInfoData.size() )
    {
        m_TagInfoData.removeAt(rowIndex);
    }
    emit layoutChanged();
}

int CTagInfoModel::rowCount(const QModelIndex &parent) const
{
    return m_TagInfoData.size();
}

QVariant CTagInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > m_TagInfoData.size())
    {
        return QVariant();
    }

    CTagInfo eleData = m_TagInfoData.at( index.row() );

    switch (role)
    {
    case TagIDRole:
    {
        return eleData.iTagID();
    }
    case MapIDRole:
    {
        return eleData.iMapID();
    }
    case BatteryRole:
    {
        return eleData.iBattery();
    }
    case PosXRole:
    {
        return eleData.iPosX();
    }
    case PosYRole:
    {
        return eleData.iPosY();
    }
    case PosZRole:
    {
        return eleData.iPosZ();
    }
    case StaticTimeRole:
    {
        return eleData.iStaticTime();
    }
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CTagInfoModel::roleNames() const
{
    return m_roleName;
}
