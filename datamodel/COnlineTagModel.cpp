#include "COnlineTagModel.h"

COnlineTagInfoModel::COnlineTagInfoModel(QObject *parent)
{
    m_roleName.insert(UserNameRole, "userName");
    m_roleName.insert(UserIDRole, "userID");
    m_roleName.insert(UserDepartmentRole, "department");
    m_roleName.insert(UserRole, "userRole");
    m_roleName.insert(TagIDRole, "tagID");
    m_roleName.insert(MapIDRole, "mapID");
    m_roleName.insert(BatteryRole, "battery");
    m_roleName.insert(PosXRole, "posX");
    m_roleName.insert(PosYRole, "posY");
    m_roleName.insert(PosZRole, "posZ");
    m_roleName.insert(StaticTimeRole, "staticTime");

}

void COnlineTagInfoModel::loadData(const vector<COnlineTagInfo> &vecTag)
{
    m_userTagInfoData.clear();

    for(auto it : vecTag)
    {
        m_userTagInfoData.push_front(it);
    }

    emit layoutChanged();
}

void COnlineTagInfoModel::addData(COnlineTagInfo &info)
{
    //去掉之前缓存的数据,再添加新数据，则一直显示taglist里面的最新信息
    for(int i = 0;i<m_userTagInfoData.size();i++)
    {
        if(m_userTagInfoData.at(i).iTagID() == info.iTagID())
        {
            m_userTagInfoData.removeAt(i);
        }
    }
    m_userTagInfoData.push_front(info);
    emit layoutChanged();
}

void COnlineTagInfoModel::addData(vector<COnlineTagInfo> &vecTag)
{
    for(auto it : vecTag)
    {
        m_userTagInfoData.push_back(it);
    }
    emit layoutChanged();
}

void COnlineTagInfoModel::deleteRow(int &rowIndex)
{
    if( rowIndex>=0 && rowIndex<m_userTagInfoData.size() )
    {
        m_userTagInfoData.removeAt(rowIndex);
    }
    emit layoutChanged();
}

void COnlineTagInfoModel::deleteRow(int tagID)
{

}

int COnlineTagInfoModel::rowCount(const QModelIndex &parent) const
{
    return m_userTagInfoData.size();
}

QVariant COnlineTagInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > m_userTagInfoData.size())
    {
        return QVariant();
    }

    COnlineTagInfo eleData = m_userTagInfoData.at( index.row() );

    switch (role)
    {
    case TagIDRole:
    {
        return QString::number(eleData.iTagID());
    }
    case MapIDRole:
    {
        return QString::number(eleData.iMapID());
    }
    case BatteryRole:
    {
        return QString::number(eleData.iBattery());
    }
    case PosXRole:
    {
        return QString::number(eleData.iPosX());
    }
    case PosYRole:
    {
        return QString::number(eleData.iPosY());
    }
    case PosZRole:
    {
        return QString::number(eleData.iPosZ());
    }
    case StaticTimeRole:
    {
        return QString::number(eleData.iStaticTime());
    }
    case UserNameRole:
    {
        return QString::fromStdString(eleData.strUsername());
    }
    case UserIDRole:
    {
        return QString::fromStdString(eleData.strUserID());
    }
    case UserDepartmentRole:
    {
        return QString::fromStdString(eleData.strDepartment());
    }
    case UserRole:
    {
        return QString::fromStdString(eleData.strRole());
    }
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> COnlineTagInfoModel::roleNames() const
{
    return m_roleName;
}
