#include "CWebSocketServer.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMap>
#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QBitmap>


CWebSocketServer::CWebSocketServer()
{
    m_WebSocketServer=new QWebSocketServer("server",QWebSocketServer::NonSecureMode);
    m_WebSocketServer->setMaxPendingConnections(20);

    connect(m_WebSocketServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));

    startServer();

    QString aaa= getLocalIP();

    qDebug()<<"sdasdsadasdasdasd"<<aaa;
}

CWebSocketServer::~CWebSocketServer()
{

}

void CWebSocketServer::startServer()
{

    //开始服务
    int i_port = 8195;
    m_WebSocketServer->listen(QHostAddress::Any,i_port);
    qDebug()<<"ttttttttttttttttttttttt";
}

void CWebSocketServer::stopServer()
{
    m_WebSocketServer->close();
}

void CWebSocketServer::test1()
{

}

QString CWebSocketServer::getLocalIP()
{
    QString hostAddr = "";
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();

    //排除虚拟机地址
    for (int i = 0; i < nCnt; i++) {
        if (nets[i].hardwareAddress() == "00:50:56:C0:00:01") {
            nets.removeAt(i);
            break;
        }
    }
    nCnt = nets.count();
    for (int i = 0; i < nCnt; i++) {
        if (nets[i].hardwareAddress() == "00:50:56:C0:00:08") {
            nets.removeAt(i);
            break;
        }
    }
    foreach(QNetworkInterface interface, nets) {
        //排除不在活动的IP
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && interface.flags().testFlag(QNetworkInterface::IsRunning)) {
            QList<QNetworkAddressEntry> entryList = interface.addressEntries();
            foreach(QNetworkAddressEntry entry, entryList) {
                QHostAddress hostAddress = entry.ip();

                if (hostAddr.isEmpty()) {
                    //排除本地地址
                    if (hostAddress != QHostAddress::LocalHost && hostAddress.toIPv4Address()) {
                        quint32 nIPV4 = hostAddress.toIPv4Address();

                        //本地链路地址
                        quint32 nMinRange = QHostAddress("169.254.1.0").toIPv4Address();
                        quint32 nMaxRange = QHostAddress("169.254.254.255").toIPv4Address();
                        //排除链路地址
                        if ((nIPV4 >= nMinRange) && (nIPV4 <= nMaxRange))
                            continue;
                        hostAddr = hostAddress.toString();
                        return hostAddr;
                    }
                }
            }
        }
    }
}

void CWebSocketServer::parseLabelMeg(QJsonArray &array)
{
    //标签卡的数据为7个JSON对象组合而成,依次解析即可
    int tagId = 0;
    int coordX = 0;
    int coordY = 0;
    int coordZ = 0;
    int staticTime = 0;
    int mapId = 0;
    int battery = 0;

    for (int i = 0; i < array.size(); i++) {
        if (array.at(i).isObject()) {
            QJsonObject object = array.at(i).toObject();
            tagId = object.value("TagId").toInt();
            coordX = object.value("X").toInt() / 1000;
            coordY = object.value("Y").toInt() / 1000;
            coordZ = object.value("Z").toInt() / 1000;
            staticTime = object.value("StaticTime").toInt();
            mapId = object.value("MapId").toInt();
            battery = object.value("Battery").toInt();
        }
    }

    //查询人的信息
    qDebug()<<"*********tagId****"<<tagId;

    //显示坐标位置
    emit setCurCoord(coordX,coordY);
}

void CWebSocketServer::parseLabelMeg(QJsonObject &object)
{
    //标签卡的数据为7个JSON对象组合而成,依次解析即可
    int tagId = 0;
    int coordX = 0;
    int coordY = 0;
    int coordZ = 0;
    int staticTime = 0;
    int mapId = 0;
    int battery = 0;

    tagId = object.value("TagId").toInt();
    coordX = object.value("X").toInt() / 1000;
    coordY = object.value("Y").toInt() / 1000;
    coordZ = object.value("Z").toInt() / 1000;
    staticTime = object.value("StaticTime").toInt();
    mapId = object.value("MapId").toInt();
    battery = object.value("Battery").toInt();

    //查询人的信息
    qDebug()<<"*********tagId****"<<tagId;

}

//连接成功
void CWebSocketServer::onNewConnection()
{

    qDebug() << "hello";
    pSocket = m_WebSocketServer->nextPendingConnection();

    connect(pSocket,SIGNAL(textMessageReceived(QString)),this,SLOT(processTextMessage(QString)));
    connect(pSocket,SIGNAL(binaryMessageReceived(QByteArray)),this,SLOT(processByteArrayMessage(QByteArray)));
    connect(pSocket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));

}

//连接断开
void CWebSocketServer::socketDisconnected()
{

}

void CWebSocketServer::processTextMessage(QString message)
{



}

//数据是JSON格式，解析后判断是基站相关还是标签卡相关(对象包括数组）
void CWebSocketServer::processByteArrayMessage(QByteArray array)
{

    qDebug()<<array;
    QJsonObject groupObj;
    QJsonDocument m_document;

    QJsonParseError error;
    m_document = QJsonDocument::fromJson(array, &error);

    if (m_document.isObject()) {
        groupObj = m_document.object();
    }

    if (groupObj.contains("MsgType")) {
        //开始判断报文类型
        int megType =  groupObj.value("MsgType").toInt();
        qDebug() <<megType;
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

        for (int i = 0; i < mesArray.size(); i++) {
            if (mesArray.at(i).isObject())
            {
                QJsonObject object = mesArray.at(i).toObject();
                parseLabelMeg(object);

            }
        }
    }
}

//数据是JSON格式，解析后判断是基站相关还是标签卡相关
//void CWebSocketServer::processByteArrayMessage(QByteArray array)
//{
//    qDebug()<<array;

//    QJsonObject groupObj;
//    QJsonDocument m_document;

//    QJsonParseError error;
//    m_document = QJsonDocument::fromJson(array, &error);


//    //解析JSON数组，数组里面还包括JSON对象和JSON数组

//    QJsonArray mesArray;

//    //步骤1：获取对应的QJsonArray数组
//    if (m_document.isArray()) {
//        mesArray = m_document.array();

//        //步骤2：用下标访问的方式来获取值（QJsonValue）,如果其中一个值是对象（QJsonObject）,就获取这个对象，然后按照对象的解析方法来解析。
//        for (int i = 0; i < array.size(); i++) {
//            if (mesArray.at(i).isObject())
//            {
//                QJsonObject object = mesArray.at(i).toObject();

//                if (object.contains("MsgType")) {

//                    //开始判断报文类型
//                    int megType =  object.value("MsgType").toInt();
//                    qDebug() <<megType;

//                    //报文为基站则暂时不管，为标签卡则处理
//                    if(megType == 1)
//                    {
//                        return;
//                    }
//                }

//                //解析标签卡的数据
//                if(object.contains("AncList"))
//                {

//                    QJsonArray lableArray = object.value("AncList").toArray();
//                    parseLabelMeg(lableArray);
//                }
//            }
//        }
//    }
//}
