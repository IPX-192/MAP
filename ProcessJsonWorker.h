#ifndef PROCESSJSONWORKER_H
#define PROCESSJSONWORKER_H

#include <QObject>
#include<QThread>
#include<QString>
#include<vector>
#include <QtWebSockets/QWebSocket>
#include <datamanager/CTagInfo.h>
#include "./datamanager/CDevInfo.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>





class ProcessJsonWorker : public QThread
{
    Q_OBJECT
public:
    explicit ProcessJsonWorker(QWebSocket *ws,vector<CDevInfo> &vec, QObject *parent = nullptr);
protected:
    void run() override;

signals:
    void finish(int x,int y,int tagId,CTagInfo tagInfo,QString &message);

public slots:
private:
    QString m_message;
   // vector<CDevInfo> m_vec;
    QWebSocket *m_ws;
   // CClientSystem m_ClientSystem;
    QJsonObject jObj;
    CTagInfo tagInfo;
    vector<CDevInfo> m_vecDevInfo;




};

#endif // PROCESSJSONWORKER_H
