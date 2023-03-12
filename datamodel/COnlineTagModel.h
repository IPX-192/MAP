#ifndef CONLINETAGMODEL_H
#define CONLINETAGMODEL_H

#include <QAbstractListModel>
#include "../datamanager/COnlineTagInfo.h"

using namespace std;

//在线信息显示Model
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

    //加载在线标签数据进行显示
    void loadData(const vector<COnlineTagInfo> &vecTag);

    //在线标签表添加数据
    void addData(COnlineTagInfo &info);

    //在线标签表添加批量数据
    void addData(vector<COnlineTagInfo> &vecTag);

    //删除一行
    void deleteRow(int &rowIndex);

    //根据tagID删除一行数据
    void deleteRow(int tagID);

    //删除表格所有数据
    void deleteAll();

    //检查数据是否需要更新
    bool checkTagInfoUpdate(COnlineTagInfo &info);

public:
    //QAbstractListModel 必须要重载的类
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    //在线标签数据
    QVector< COnlineTagInfo > m_userTagInfoData;
    QHash<int, QByteArray> m_roleName;
};

#endif // CONLINETAGMODEL_H
