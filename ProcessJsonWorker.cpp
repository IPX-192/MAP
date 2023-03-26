#include "ProcessJsonWorker.h"

#include <datamanager/CTagInfo.h>


ProcessJsonWorker::ProcessJsonWorker(QWebSocket *ws,vector<CDevInfo> &vec,QObject *parent) : QThread(parent)
{

    m_ws=ws;
    //m_FirstResv=false;4
    m_vecDevInfo=vec;

}

void ProcessJsonWorker::run()
{
    connect(m_ws,&QWebSocket::textMessageReceived,this,[=](QString message){
        m_message=message;

        QJsonObject groupObj;
        QJsonDocument m_document;
        QJsonParseError error;

        m_document = QJsonDocument::fromJson(m_message.toUtf8(), &error);

        if (m_document.isObject()) {
            groupObj = m_document.object();
        }

        if (groupObj.contains("MsgType")) {
            //开始判断报文类型
            int megType =  groupObj.value("MsgType").toInt();

            //报文为基站则暂时不管，为标签卡则处理
            if(megType == 1)
            {
                return;
            }
        }
        //开始解析标签卡数组，数组里面是每个成员的数据包
        if (groupObj.contains("TagList")) {
            QJsonArray mesArray = groupObj.value("TagList").toArray();
            //这里的解析为JSON数组组合JSON对象
            if (mesArray.at(0).isObject())
            {
                jObj = mesArray.at(0).toObject();
            }
        }
        int tagId = 0;
        int coordX = 0;      //单位毫米
        int coordY = 0;      //单位毫米
        int coordZ = 0;      //单位毫米
        int staticTime = 0;
        int mapId = 0;
        int battery = 0;
        int devNum = 0;
        // Mythread *devNumThread=new Mythread;
        tagId = jObj.value("TagId").toInt();
        coordX = jObj.value("X").toInt();
        coordY = jObj.value("Y").toInt();
        coordZ = jObj.value("Z").toInt();
        staticTime = jObj.value("StaticTime").toInt();
        mapId = jObj.value("MapId").toInt();
        battery = jObj.value("Battery").toInt();

        //把毫米换算成像素点,1000个像素点为500m,即一个像素点为500mm
        int PixelX = coordX / 340;
        int PixelY = coordY / 340;


        //    emit sendDevData(m_vecDevInfo,coordX);
        //    emit startDevNumThread();


        //查询人的信息
        //qDebug()<<"*********tagId****"<<tagId;

        CDevInfo dev;
        CDevInfo dev1;

        //显示坐标位置
        for (std::vector<CDevInfo>::iterator it = m_vecDevInfo.begin(); it != m_vecDevInfo.end(); ++it)
        {
            // 使用迭代器访问每个元素
            dev = *it;

            if(it + 1 < m_vecDevInfo.end())
            {
                dev1 = *(it + 1);

                //如果X坐标小于第一个设备

                if(coordX <= dev.iDevPos())
                {
                    devNum = dev.iDevID();
                    break;
                }

                //如果X坐标位于两者之间
                if(coordX > dev.iDevPos() && coordX <= dev1.iDevPos())
                {
                    devNum = dev1.iDevID();
                    break;
                }
                else
                {
                    devNum = 0;
                }
            }
        }

        //显示对应的表格数据

        tagInfo.setIPosX(coordX);
        tagInfo.setIPosY(coordY);
        tagInfo.setIPosZ(devNum);
        tagInfo.setIMapID(mapId);
        tagInfo.setITagID(tagId);
        tagInfo.setIBattery(battery);
        tagInfo.setIStaticTime(staticTime);
        //qDebug()<<PixelX<<"+"<<PixelY<<"+"<<tagId<<"+"<<tagInfo.iPosZ();

        emit finish(PixelX,PixelY,tagId,tagInfo,m_message);
    });
    //转发
    //  qDebug()<<m_message;


    exec();


}
