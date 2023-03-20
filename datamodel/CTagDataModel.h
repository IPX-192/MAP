#ifndef CTAGDATAMODEL_H
#define CTAGDATAMODEL_H


#include <QAbstractListModel>
#include "../datamanager/CTagData.h"

using namespace std;

//标签信息显示model
class CTagDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MODEL_ROLE
    {
        TagIDRole = 0,
        DataIDRole,
        MapIDRole,
        BatteryRole,
        PosXRole,
        PosYRole,
        PosZRole,
        StaticTimeRole,
        UserNameRole,
        UserDepartmentRole,
        UserRole,
        UserIDRole,
        SaveTime
    };

public:
    explicit CTagDataModel(QObject *parent = nullptr);

    //标签数据进行显示
    void loadData(const vector<CTagData> &vecTag);

    //标签表添加数据
    void addData(CTagData &info);

    //标签信息
    void addData(vector<CTagData> &vecTag);

    //删除一行
    void deleteRow(QString userID);

    //删除所有
    void delAllData();

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector< CTagData > m_TagData;
    QHash<int, QByteArray> m_roleName;
};

#endif // CTAGDATAMODEL_H
