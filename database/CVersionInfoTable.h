#ifndef CVERSIONINFOTABLE_H
#define CVERSIONINFOTABLE_H

#include "CAbstractConfigInfo.h"

//软件版本号（预留接口,暂时不用）
class CVersionInfoTable : public CAbstractConfigInfo
{
public:
    CVersionInfoTable(MapSysDatabase *dataBase);
    ~CVersionInfoTable();

    virtual bool Check_Config_Table();

    //获取软件版本号
    string getVersionInfo();

    //更新软件版本号
    bool updateVersionInfo(const QString &info);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CVERSIONINFOTABLE_H
