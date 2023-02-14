#ifndef CTAGINFOMODEL_H
#define CTAGINFOMODEL_H

#include <QAbstractListModel>
#include "../datamanager/CTagInfo.h"

using namespace std;

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

    void loadData(const vector<CTagInfo> &vecTag);
    void addData(CTagInfo &info);
    void addData(vector<CTagInfo> &vecTag);
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
