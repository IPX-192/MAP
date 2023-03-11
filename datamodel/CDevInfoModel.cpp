#include "CDevInfoModel.h"

CDevInfoModel::CDevInfoModel(QObject *parent)
{
    m_roleName.insert(DevNameRole, "devName");
    m_roleName.insert(DevPosRole, "devPos");
    m_roleName.insert(BHighlightRole, "bLight");

    CDevInfo test;
    test.setIDevID(1);
    test.setIDevPos(20000);
    test.setBHighlight(true);
    test.setStrDevName("dev1");
    m_devInfoData.push_back(test);
}

void CDevInfoModel::loadData(const vector<CDevInfo> &vecTag)
{
    m_devInfoData.clear();

    for(auto it : vecTag)
    {
        m_devInfoData.push_front(it);
    }

    emit layoutChanged();
}

void CDevInfoModel::deleteAll()
{
    m_devInfoData.clear();
    emit layoutChanged();
}

void CDevInfoModel::updateRowData(bool bHighlight, QString devName)
{
    for(auto it : m_devInfoData)
    {
        if(it.strDevName() == devName.toStdString())
        {
            it.setBHighlight(bHighlight);
        }
    }
    emit layoutChanged();
}

QVariant CDevInfoModel::get(int index, const QString &roleName) const
{
    QModelIndex modelIndex = this->index(index);
    QVariant value = data(modelIndex, roleNames().key(roleName.toUtf8(), Qt::DisplayRole));
    return value;
}

int CDevInfoModel::rowCount(const QModelIndex &parent) const
{
    return m_devInfoData.size();
}

QVariant CDevInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > m_devInfoData.size())
    {
        return QVariant();
    }

    CDevInfo eleData = m_devInfoData.at( index.row() );

    switch (role)
    {
    case DevNameRole:
    {
        return QString::fromStdString(eleData.strDevName());
    }
    case DevPosRole:
    {
        return eleData.iDevPos();
    }
    case BHighlightRole:
    {
        return eleData.bHighlight();
    }
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CDevInfoModel::roleNames() const
{
    return m_roleName;
}
