#include "CWebSocketServer.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMap>
#include <QFileInfo>
#include <QGuiApplication>
#include <QHostAddress>
#include <QDir>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QBitmap>


CWebSocketServer::CWebSocketServer()
{
    m_WebSocketServer=new QWebSocketServer("server",QWebSocketServer::NonSecureMode);
    m_WebSocketServer->setMaxPendingConnections(20);

    connect(m_WebSocketServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
    connect(&m_RecvTimer,&QTimer::timeout,this,&CWebSocketServer::onRecvDataFinish);

    startServer();

    QString serverIP = getLocalIP();
    emit sendCurServerAddress(serverIP);

    qDebug()<<"sdasdsadasdasdasd"<<serverIP;
}

CWebSocketServer::~CWebSocketServer()
{

}

void CWebSocketServer::startServer()
{
    //开始服务
    int i_port = 8195;
    m_WebSocketServer->listen(QHostAddress::Any,i_port);
}

void CWebSocketServer::stopServer()
{
    m_WebSocketServer->close();
}

bool CWebSocketServer::copyImageFile(QString image)
{
    //去掉file:///
    image = image.mid(8);
    //获取需要拷贝的文件名称
    QFileInfo info(image);

    //获取可执行文件目录
    QString appPath = qApp->applicationDirPath();
    //查询该目录下是否存在文件夹LogoFile，没有则创建
    QString LogoDir = appPath + "/MapImg";
    QDir dir(LogoDir);
    if(!dir.exists())
    {
        dir.mkdir(LogoDir);
    }

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString   current_date = current_date_time.toString("hhmmsszzz");

    LogoDir += "/";
    //将logo重新命名
    LogoDir += "map" + current_date;
    QString m_suffix =  image.right(4);
    LogoDir += m_suffix;

    //拼接报告名
    QString reportLogo = current_date + m_suffix;

    //清空目录(保留默认logo)
    dir.setFilter(QDir::Files);
    int fileCount = static_cast<int>(dir.count());
    for (int i = 0; i < fileCount; i++)
    {
        dir.remove(dir[i]);
    }

    if(!QFile::copy(image,LogoDir))
    {
        return false;
    }

    return  true;

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
    emit setCurCoord(coordX,coordY,tagId);
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

    //显示坐标位置
    emit setCurCoord(coordX,coordY,tagId);

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
    //m_bRecvData = true;
    m_RecvTimer.stop();
    emit clearDrawCoord();
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

    m_RecvTimer.start(2000);   //超过两秒没有新数据上发，则认为传输已经结束，清理界面上的坐标
}

void CWebSocketServer::onRecvDataFinish()
{
    emit clearDrawCoord();
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
