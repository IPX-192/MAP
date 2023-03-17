#ifndef CDATABASEMANAGE_H
#define CDATABASEMANAGE_H

#include "CUserInfoTable.h"
#include "CMapOriginConfig.h"
#include "CTagInfoTable.h"
#include "CVersionInfoTable.h"
#include "CTagDataTable.h"
#include "CDevInfoTable.h"
#include "CDevInfoConfig.h"
#include "mapsysdatabase.hpp"

//数据库管理类
class CDatabaseManage
{
public:
    ~CDatabaseManage();

public:
    //获取所有数据表格对象
    CUserInfoTable *pUserInfo() const;
    CMapOriginConfig *pConfigMapOrigin() const;
    CTagInfoTable *pTagInfo() const;
    CVersionInfoTable *pVersionInfo() const;
    CTagDataTable *pTagData() const;
    CDevInfoTable *pDevInfo() const;
    CDevInfoConfig *pDevConfig() const;

    //获取单例
    static CDatabaseManage *GetInstance();

private:
    CDatabaseManage();

    CDatabaseManage(const CDatabaseManage &manager);
    CDatabaseManage &operator = (const CDatabaseManage &manager);

    //实例对象
    static CDatabaseManage		*s_pManagerInstance;
    static QMutex				s_csManager_Instance_Safe;

    //------------------------------配置文件相关操作-------------------------------
    //检查配置数据库，包括：文件存在、数据库升级、配置默认值
    bool	checkConfigDatabase();

    //在检查完数据库之后初始化配置逻辑处理类对象
    void	initailizeConfigObject();

    //检查数据表中是否存在配置数据，如果不存在写入默认项
    bool	checkConfigDatatable();

    //检查数据库版本
    bool    checkDatabaseVersion();

    //更新检查同时更新
    bool    checkAndUpdateTable(CAbstractConfigInfo *info, bool bUpdate);

    //检查文件是否存在
    bool    isFileExist(const string &fullPath, bool bCreat = false);

    //检查路径是否存在
    bool    isDirExist(const string &fullPath, bool bCreat = false);

    //删除文件
    bool    deleteFileOrFolder(const string &fullPath);

    //表格操作对象
    CUserInfoTable *m_pUserInfo;
    CMapOriginConfig *m_pConfigMapOrigin;
    CTagInfoTable *m_pTagInfo;
    CVersionInfoTable *m_pVersionInfo;
    CTagDataTable *m_pTagData;
    CDevInfoTable *m_pDevInfo;
    CDevInfoConfig *m_pDevConfig;

    //配置文件路径
    string				  m_strConfigDBPath{""};
    MapSysDatabase       *m_pConfigDatabase{nullptr};

    //配置文件是否重新生成
    bool                  m_bReCreated{false};

    //是否需要对数据进行升级
    bool				  m_bUpgrade{false};
};

#endif // CDATABASEMANAGE_H
