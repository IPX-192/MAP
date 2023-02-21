#ifndef CTAGINFOMODEL_H
#define CTAGINFOMODEL_H

#include <QAbstractListModel>
#include "../datamanager/CTagInfo.h"

using namespace std;

//标签信息显示model
class CTagInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MODEL_ROLE
    {
        TagIDRole = 0,
        MapIDRole,
        BatteryRole,
        PosXRole,
        PosYRole,
        PosZRole,
        StaticTimeRole
    };

public:
    explicit CTagInfoModel(QObject *parent = nullptr);

    //标签数据进行显示
    void loadData(const vector<CTagInfo> &vecTag);

    //标签表添加数据
    void addData(CTagInfo &info);

    //标签信息
    void addData(vector<CTagInfo> &vecTag);

    //删除一行
    void deleteRow(int &rowIndex);

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector< CTagInfo > m_TagInfoData;
    QHash<int, QByteArray> m_roleName;
};

#endif // CTAGINFOMODEL_H
