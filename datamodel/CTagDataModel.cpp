#include "CTagDataModel.h"

CTagDataModel::CTagDataModel(QObject *parent)
{
    m_roleName.insert(TagIDRole, "tagID");
    m_roleName.insert(DataIDRole, "dataID");
    m_roleName.insert(MapIDRole, "mapID");
    m_roleName.insert(BatteryRole, "battery");
    m_roleName.insert(PosXRole, "posX");
    m_roleName.insert(PosYRole, "posY");
    m_roleName.insert(PosZRole, "posZ");
    m_roleName.insert(StaticTimeRole, "staticTime");
    m_roleName.insert(UserNameRole, "userName");
    m_roleName.insert(UserIDRole, "userID");
    m_roleName.insert(UserDepartmentRole, "department");
    m_roleName.insert(UserRole, "userRole");
    m_roleName.insert(SaveTime, "saveTime");
}

void CTagDataModel::loadData(const vector<CTagData> &vecTag)
{
    m_TagData.clear();

    for(auto it : vecTag)
    {
        m_TagData.push_front(it);
    }

    emit layoutChanged();
}

void CTagDataModel::addData(CTagData &info)
{
    m_TagData.push_front(info);

    emit layoutChanged();
}

void CTagDataModel::addData(vector<CTagData> &vecTag)
{
    for(auto it : vecTag)
    {
        m_TagData.push_back(it);
    }
    emit layoutChanged();
}

void CTagDataModel::deleteRow(QString dataID)
{
    if(m_TagData.count() > 0)
    {
        for(int i = 0 ; i< m_TagData.count() ; i++)
        {
            if(m_TagData[i].iDataID() == dataID.toInt())
            {
                m_TagData.remove(i);
            }
        }
    }

    emit layoutChanged();
}

void CTagDataModel::delAllData()
{
    m_TagData.clear();
    emit layoutChanged();
}

int CTagDataModel::rowCount(const QModelIndex &parent) const
{
    return m_TagData.size();
}

QVariant CTagDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > m_TagData.size())
    {
        return QVariant();
    }

    CTagData eleData = m_TagData.at( index.row() );

    switch (role)
    {
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
    case TagIDRole:
    {
        return QString::number(eleData.iTagID());
    }
    case DataIDRole:
    {
        return QString::number(eleData.iDataID());
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
    case SaveTime:
        return QString::fromStdString(eleData.saveTime());

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CTagDataModel::roleNames() const
{
    return m_roleName;
}
