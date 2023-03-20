#include "CDevInfoModel.h"

CDevInfoModel::CDevInfoModel(QObject *parent)
{
    m_roleName.insert(DevNameRole, "devName");
    m_roleName.insert(DevPosRole, "devPos");
    m_roleName.insert(BHighlightRole, "bLight");

    m_timer.setInterval(800);

    // 设置定时器的触发事件
    QObject::connect(&m_timer, &QTimer::timeout, this, [&](){
        initDevStatus();
    });

    // 启动定时器
    m_timer.start();

    //    CDevInfo test;
    //    test.setIDevID(1);
    //    test.setIDevPos(20000);

    //    test.setBHighlight(true);
    //    test.setStrDevName("dev1");
    //    m_devInfoData.push_back(test);

    //    test.setIDevID(2);
    //    test.setIDevPos(20000);
    //    test.setBHighlight(false);
    //    test.setStrDevName("dev2");
    //    m_devInfoData.push_back(test);

    //    test.setIDevID(3);
    //    test.setIDevPos(50000);
    //    test.setBHighlight(true);
    //    test.setStrDevName("dev3");
    //    m_devInfoData.push_back(test);
}

void CDevInfoModel::loadData(const vector<CDevInfo> &vecTag)
{
    if(vecTag.size() <= 0)
    {
        return;
    }

    m_devInfoData.clear();

    for(auto it = vecTag.begin(); it != vecTag.end(); ++it)
    {
        CDevInfo info;
        info.setIDevID(it->iDevID());
        info.setIDevPos(it->iDevPos());
        info.setStrDevName(it->strDevName());
        info.setBHighlight(false);
        m_devInfoData.push_back(info);
    }

    //设置最大距离
    auto last = std::find(vecTag.begin(), vecTag.end(), vecTag.back());
    m_maxPos = last->iDevPos() > m_devInfoData[0].iDevPos() ? last->iDevPos() : m_devInfoData[0].iDevPos();

    //设置位置间距
    m_spacing = m_devInfoData[0].iDevPos();

    emit layoutChanged();
}

void CDevInfoModel::deleteAll()
{
    m_maxPos = 0;
    m_spacing = 0;
    m_devInfoData.clear();
    emit layoutChanged();
}

void CDevInfoModel::updateRowData(bool bHighlight, int index)
{
    if(index >=0 && index < m_devInfoData.size())
    {
        m_devInfoData[index].setBHighlight(bHighlight);
        emit layoutChanged();
    }
}

int CDevInfoModel::dataNum()
{
    return  m_devInfoData.size();
}

bool CDevInfoModel::updateDevStatus(int pos)
{
    if(pos <= 0 || pos > m_maxPos)
    {
        return false;
    }

    int index = pos / m_spacing - 1;

    if(index >= 0)
    {
        updateRowData(true, index);
    }

    return true;
}

void CDevInfoModel::initDevStatus()
{
    for(int index = 0; index < m_devInfoData.size(); index++)
    {
        m_devInfoData[index].setBHighlight(false);
    }
    emit layoutChanged();
}

bool CDevInfoModel::checkDevEnable()
{
    return true;
}

void CDevInfoModel::setTimerState(bool bActive)
{
    if(bActive)
    {
        m_timer.start();
    }
    else
    {
        m_timer.stop();
    }
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

int CDevInfoModel::getMaxPos() const
{
    return m_maxPos;
}

int CDevInfoModel::getLastDevID() const
{
    if(m_devInfoData.size())
    {
        return m_devInfoData.last().iDevID();
    }
    return 0;
}

void CDevInfoModel::getDevNum(int curX)
{
    m_devInfoData.size();
}
