#ifndef CDEVINFOMODEL_H
#define CDEVINFOMODEL_H

#include <QAbstractListModel>
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
    void updateRowData(bool bHighlight, QString devName);

    //获取标签位置
    QString getDevNameByPos(int pos);

    Q_INVOKABLE QVariant get(int index, const QString &roleName) const;

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    //在线标签数据
    QVector< CDevInfo > m_devInfoData;
    QHash<int, QByteArray> m_roleName;
};

#endif // CDEVINFOMODEL_H
