#ifndef CONLINETAGMODEL_H
#define CONLINETAGMODEL_H

#include <QAbstractListModel>
#include "../datamanager/COnlineTagInfo.h"

using namespace std;

class COnlineTagInfoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MODEL_ROLE
    {
        TagIDRole = 0,
        UserNameRole,
        UserIDRole,
        UserDepartmentRole,
        UserRole,
        MapIDRole,
        BatteryRole,
        PosXRole,
        PosYRole,
        PosZRole,
        StaticTimeRole
    };

public:
    explicit COnlineTagInfoModel(QObject *parent = nullptr);

    void loadData(const vector<COnlineTagInfo> &vecTag);
    void addData(COnlineTagInfo &info);
    void addData(vector<COnlineTagInfo> &vecTag);
    void deleteRow(int &rowIndex);
    void deleteRow(int tagID);
    void deleteAll();

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;


private:
    QVector< COnlineTagInfo > m_userTagInfoData;
    QHash<int, QByteArray> m_roleName;
};

#endif // CONLINETAGMODEL_H
