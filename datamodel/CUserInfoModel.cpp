#include "CUserInfoModel.h"

CUserInfoModel::CUserInfoModel(QObject *parent)
{
    m_roleName.insert(IsChooseRole, "isChoose");
    m_roleName.insert(UserNameRole, "userName");
    m_roleName.insert(UserIDRole, "userID");
    m_roleName.insert(UserDepartmentRole, "department");
    m_roleName.insert(UserRole, "userRole");
    m_roleName.insert(UserTagID, "userTagID");
}

void CUserInfoModel::loadData(const vector<CUserInfo> &vecUser)
{
    m_userInfoData.clear();

    for(auto it : vecUser)
    {
        m_userInfoData.push_front(it);
    }

    emit layoutChanged();
}

void CUserInfoModel::addData(CUserInfo &info)
{
    m_userInfoData.push_front(info);

    emit layoutChanged();
}

void CUserInfoModel::addData(vector<CUserInfo> &vecUser)
{
    for(auto it : vecUser)
    {
        m_userInfoData.push_back(it);
    }
    emit layoutChanged();
}

void CUserInfoModel::deleteRow(int &rowIndex)
{
    if( rowIndex>=0 && rowIndex<m_userInfoData.size() )
    {
        m_userInfoData.removeAt(rowIndex);
    }
    emit layoutChanged();
}

int CUserInfoModel::rowCount(const QModelIndex &parent) const
{
    return m_userInfoData.size();
}

QVariant CUserInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > m_userInfoData.size())
    {
        return QVariant();
    }

    CUserInfo eleData = m_userInfoData.at( index.row() );

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
    case UserTagID:
    {
        return eleData.itagID();
    }
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CUserInfoModel::roleNames() const
{
    return m_roleName;
}
