#ifndef CVERSIONINFOTABLE_H
#define CVERSIONINFOTABLE_H

#include "CAbstractConfigInfo.h"

class CVersionInfoTable : public CAbstractConfigInfo
{
public:
    CVersionInfoTable(MapSysDatabase *dataBase);
    ~CVersionInfoTable();

    virtual bool Check_Config_Table();

    string getVersionInfo();
    bool updateVersionInfo(const QString &info);

private:
    MapSysDatabase *m_pDatabase{nullptr};
};

#endif // CVERSIONINFOTABLE_H
