#include "CDatabaseManage.h"
#include <QCoreApplication>
#include <QFile>
#include <QDir>

CDatabaseManage::CDatabaseManage()
    :m_pUserInfo(nullptr)
    ,m_pConfigMapOrigin(nullptr)
    ,m_pTagInfo(nullptr)
    ,m_pVersionInfo(nullptr)
    ,m_pTagData(nullptr)
    ,m_pDevInfo(nullptr)
    ,m_pDevConfig(nullptr)
{
    //检查数据库表格是否存在
    checkConfigDatabase();

    //初始化表格对象
    initailizeConfigObject();

    //检查是否需要更新表格内容
    checkConfigDatatable();
}

CDatabaseManage::~CDatabaseManage()
{
    //释放所有指针对象
    if( m_pUserInfo != nullptr)
    {
        delete m_pUserInfo;
        m_pUserInfo = nullptr;
    }

    if( m_pConfigMapOrigin != nullptr)
    {
        delete m_pConfigMapOrigin;
        m_pConfigMapOrigin = nullptr;
    }

    if( m_pTagInfo != nullptr)
    {
        delete m_pTagInfo;
        m_pTagInfo = nullptr;
    }

    if( m_pVersionInfo != nullptr)
    {
        delete m_pVersionInfo;
        m_pVersionInfo = nullptr;
    }

    if( m_pTagData != nullptr)
    {
        delete m_pTagData;
        m_pTagData = nullptr;
    }

    if( m_pDevInfo != nullptr)
    {
        delete m_pDevInfo;
        m_pDevInfo = nullptr;
    }

    if( m_pDevConfig != nullptr)
    {
        delete m_pDevConfig;
        m_pDevConfig = nullptr;
    }
}

//检查配置数据库，包括：文件存在、数据库升级、配置默认值
bool CDatabaseManage::checkConfigDatabase()
{
    bool bAvailable = false;

    ///初始化数据库文件路径
    string strCurrent_Path = QCoreApplication::applicationDirPath().toStdString();
    m_strConfigDBPath = strCurrent_Path + "/";
    m_strConfigDBPath += "MapDatabase.db";

    //如果数据库不存在，创建数据库
    if (!isFileExist(m_strConfigDBPath))
    {
        string dbFilePathConfig = "database=" + m_strConfigDBPath;

        //创建数据库,configDB("sqlite3", "MapSysDatabase.db");
        m_pConfigDatabase = new MapSysDatabase("sqlite3", dbFilePathConfig.c_str());

        //提交数据库事务，在这里会创建全部的配置项的数据库表
        m_pConfigDatabase->verbose = true;
        m_pConfigDatabase->begin();
        m_pConfigDatabase->create();
        m_pConfigDatabase->commit();

        bAvailable = true;
        m_bReCreated = true;
    }
    else
    {
        //文件存在
        string strTempDataBasePath = "database=" + m_strConfigDBPath;
        m_pConfigDatabase = new MapSysDatabase("sqlite3", strTempDataBasePath.c_str());
        if (nullptr == m_pConfigDatabase)
        {
            char log[256];
            sprintf(log, "Failed to init EvaluationRecordDatabase instance");
            std::cout << string(log) << "\n";
            return false;
        }
        else
        {
            bAvailable = true;
            m_bReCreated = true;
        }
    }

    return bAvailable;
}

//创建数据库表格对象
void CDatabaseManage::initailizeConfigObject()
{
    m_pUserInfo = new CUserInfoTable(m_pConfigDatabase);
    m_pConfigMapOrigin  = new CMapOriginConfig(m_pConfigDatabase);
    m_pTagInfo = new CTagInfoTable(m_pConfigDatabase);
    m_pVersionInfo = new CVersionInfoTable(m_pConfigDatabase);
    m_pTagData = new CTagDataTable(m_pConfigDatabase);
    m_pDevInfo = new CDevInfoTable(m_pConfigDatabase);
    m_pDevConfig = new CDevInfoConfig(m_pConfigDatabase);
}

//检查配置是否存在更新
bool CDatabaseManage::checkConfigDatatable()
{
    bool bRet = true;
    //版本表仅更新
    bRet &= checkAndUpdateTable(m_pVersionInfo, false);
    bRet &= checkAndUpdateTable(m_pUserInfo, m_bUpgrade);
    bRet &= checkAndUpdateTable(m_pConfigMapOrigin, m_bUpgrade);
    bRet &= checkAndUpdateTable(m_pTagInfo, m_bUpgrade);
    bRet &= checkAndUpdateTable(m_pTagData, m_bUpgrade);
    bRet &= checkAndUpdateTable(m_pDevInfo, m_bUpgrade);
    bRet &= checkAndUpdateTable(m_pDevConfig, m_bUpgrade);
    return false;
}

//检查当前数据库版本是否匹配（预留接口）
bool CDatabaseManage::checkDatabaseVersion()
{
    //默认为不成功
    bool bSuccess = false;

    //判断配置数据是否存在
    if (m_pConfigDatabase == nullptr)
    {
        //如果不存在则重新获取
        bSuccess = false;
        return bSuccess;
    }

    //如果没有重新创建，则判断配置文件的版本
    if (!m_bReCreated)
    {
        //数据库文件版本配置为null，删除数据库文件重新生成，并且写入，默认配置
        if (m_pVersionInfo->getVersionInfo().empty())
        {
            delete m_pConfigDatabase;
            m_pConfigDatabase = nullptr;
            deleteFileOrFolder(m_strConfigDBPath);

            checkConfigDatabase();

            //写入默认配置
            m_pVersionInfo->Check_Config_Table();
        }
        else
        {
            /*
            if (!m_pVersionInfo->isLatestVersion())
            {
                m_bUpgrade = true;
            }
            */
        }
    }

    //判断是否需要升级
    if (m_pConfigDatabase->needsUpgrade())
    {
        m_bUpgrade = true;

        //升级
        m_pConfigDatabase->upgrade();
    }
    bSuccess = true;

    return bSuccess;
}

//传入数据库表格对象，检查表格是否需要更新
bool CDatabaseManage::checkAndUpdateTable(CAbstractConfigInfo *info, bool bUpdate)
{
    bool bRet = false;

    if(info != nullptr)
    {
        bRet = info->Check_Config_Table();

        if(bUpdate)
            info->Upgrade_Config_Table_Data();
    }

    return bRet;
}

//工具函数，检查文件是否存在
bool CDatabaseManage::isFileExist(const string &fullPath, bool bCreat)
{
    QString qsPath = QString::fromStdString(fullPath);
    bool ok = QFile::exists(qsPath);

    if(!ok && bCreat)
    {
        //文件夹不存在创建路径
        QString sPath = qsPath.left(qsPath.lastIndexOf('/'));
        isDirExist(sPath.toStdString(), bCreat);

        //当以Write方式打开时，若文件不存在则自动创建
        QFile file(qsPath);
        ok = file.open(QIODevice::WriteOnly);
    }

    return ok;
}

//工具函数，检查路径是否存在
bool CDatabaseManage::isDirExist(const string &fullPath, bool bCreat)
{
    QString qsTemp = QString::fromStdString(fullPath);
    QDir dir(qsTemp);

    bool bRes = false;

    if(dir.exists())
    {
        bRes = true;
    }
    else
    {
        if(bCreat)
        {
            bRes = dir.mkdir(qsTemp);
        }
    }

    return  bRes;
}

//删除文件夹，文件
bool CDatabaseManage::deleteFileOrFolder(const string &fullPath)
{
    QString strPath = QString::fromStdString(fullPath);
    if (strPath.isEmpty() || !QDir().exists(strPath))//是否传入了空的路径||路径是否存在
            return false;

    QFileInfo FileInfo(strPath);

    if (FileInfo.isFile())//如果是文件
        QFile::remove(strPath);
    else if (FileInfo.isDir())//如果是文件夹
    {
        QDir qDir(strPath);
        qDir.removeRecursively();
    }
    return true;
}

CDevInfoTable *CDatabaseManage::pDevInfo() const
{
    return m_pDevInfo;
}

CDevInfoConfig *CDatabaseManage::pDevConfig() const
{
    return m_pDevConfig;
}

CTagDataTable *CDatabaseManage::pTagData() const
{
    return m_pTagData;
}

CUserInfoTable *CDatabaseManage::pUserInfo() const
{
    return m_pUserInfo;
}

CMapOriginConfig *CDatabaseManage::pConfigMapOrigin() const
{
    return m_pConfigMapOrigin;
}

CTagInfoTable *CDatabaseManage::pTagInfo() const
{
    return m_pTagInfo;
}

CVersionInfoTable *CDatabaseManage::pVersionInfo() const
{
    return m_pVersionInfo;
}

CDatabaseManage *CDatabaseManage::GetInstance()
{
    if( s_pManagerInstance == nullptr)
    {
        s_csManager_Instance_Safe.lock();

        if(s_pManagerInstance == nullptr)
        {
            s_pManagerInstance = new CDatabaseManage();
        }

        s_csManager_Instance_Safe.unlock();
    }

    return s_pManagerInstance;
}

QMutex CDatabaseManage::s_csManager_Instance_Safe;

CDatabaseManage * CDatabaseManage::s_pManagerInstance = nullptr;
