#ifndef CDEVINFOMODEL_H
#define CDEVINFOMODEL_H

#include <QAbstractListModel>
#include "../datamanager/COnlineTagInfo.h"

class CDevInfoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MODEL_ROLE
    {

    };
    explicit CDevInfoModel(QObject *parent = nullptr);

private:
    //在线标签数据
    QVector< COnlineTagInfo > m_devInfoData;
    QHash<int, QByteArray> m_roleName;
};

#endif // CDEVINFOMODEL_H
