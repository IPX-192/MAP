#ifndef CDATABASEMANAGE_H
#define CDATABASEMANAGE_H
#include "CUserInfoTable.h"
#include "CMapOriginConfig.h"
#include "CTagInfoTable.h"

class CDatabaseManage
{
public:
    ~CDatabaseManage();
private:
    CDatabaseManage();

    CDatabaseManage(const CDatabaseManage &manager);
    CDatabaseManage &operator = (const CDatabaseManage &manager);

    //实例对象
    static CDatabaseManage		*s_pManagerInstance;
    static QMutex				s_csManager_Instance_Safe;

};

#endif // CDATABASEMANAGE_H
