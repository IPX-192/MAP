#ifndef CUSERINFOMODEL_H
#define CUSERINFOMODEL_H

#include <QAbstractListModel>
#include "../datamanager/CUserInfo.h"

class CUserInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MODEL_ROLE
    {
        IsChooseRole = 0,
        UserNameRole,
        UserIDRole,
        UserDepartmentRole,
        UserRole,
        UserTagID
    };

public:
    explicit CUserInfoModel(QObject *parent = nullptr);

    //人员信息进行显示
    void loadData(const vector<CUserInfo> &vecUser);

    //人员添加数据
    void addData(CUserInfo &info);

    //人员批量添加数据
    void addData(vector<CUserInfo> &vecUser);

    //删除一行
    void deleteRow(QString userID);

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector< CUserInfo > m_userInfoData;
    QHash<int, QByteArray> m_roleName;
};

#endif // CUSERINFOMODEL_H
