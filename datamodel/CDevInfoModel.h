#ifndef CDEVINFOMODEL_H
#define CDEVINFOMODEL_H

#include <QAbstractListModel>
#include <QTimer>
#include "../datamanager/CDevInfo.h"

class CDevInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MODEL_ROLE
    {
        DevNameRole,
        DevPosRole,
        BHighlightRole
    };

public:
    explicit CDevInfoModel(QObject *parent = nullptr);

    //标签数据进行显示
    void loadData(const vector<CDevInfo> &vecTag);

    //删除所有
    void deleteAll();

    //更新状态
    void updateRowData(bool bHighlight, int index);

    //获取设备数量
    int  dataNum();

    //更新设备状态
    bool updateDevStatus(int pos);

    //初始化所有设备状态
    void initDevStatus();

    //判断当前设备是否能添加
    bool checkDevEnable();

    //变更定时器状态
    void setTimerState(bool bActive);

    //获取当前最大位置
    int getMaxPos() const;

    //获取当前设备号
    int getLastDevID() const;

    void getDevNum(int curX);

    Q_INVOKABLE QVariant get(int index, const QString &roleName) const;

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    //在线标签数据
    QVector< CDevInfo > m_devInfoData;
    QHash<int, QByteArray> m_roleName;
    int m_maxPos{0};
    int m_spacing{0};
    QTimer m_timer;
};

#endif // CDEVINFOMODEL_H
