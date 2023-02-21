#ifndef CUSERINFOTABLE_H
#define CUSERINFOTABLE_H

#include "CAbstractConfigInfo.h"
#include "../datamanager/CUserInfo.h"

//人员信息表
class CUserInfoTable : public CAbstractConfigInfo
{
public:
    CUserInfoTable(MapSysDatabase *dataBase);
    ~CUserInfoTable();


    virtual bool Check_Config_Table();

    //添加人员信息
    bool addUserInfo(const CUserInfo &info);

    //删除人员信息（info带iD）
    bool delUserInfo(const CUserInfo &info, bool bDeleteAll = false);

    //更新人员信息
    bool updateUserInfo(const string userID, const CUserInfo &info);

    //查询获取所有人员信息
    bool getAllUserInfo(vector<CUserInfo> &vecUsers);

    //根据用户ID查找人员信息
    bool getUserInfoByID(const string &strUserID, CUserInfo &info);

    //根据标签ID查找人员信息
    bool getUserInfoByTagID(const int &tagID, CUserInfo &info);

    //判断账号是否可用
    bool checkUserIDExist(const string &strUserID, const int &tagID);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};


#endif // CUSERINFOTABLE_H
