#if !defined(EA_5E46B88C_57C5_4c3e_80A1_B23EB043FC2C_INCLUDED_)
#define EA_5E46B88C_57C5_4c3e_80A1_B23EB043FC2C_INCLUDED_

#include "litesql.hpp"
#include <QMutex>
#include <string>
#include <QString>
#include "mapsysdatabase.hpp"

using std::string;

#define RESERVE_BASE_MAX  100000
#define UNKNOWN_ID -1000

using namespace Database;
using namespace litesql;

/**
 * 配置逻辑父类
 */
class CAbstractConfigInfo
{

public:
    CAbstractConfigInfo();
    virtual ~CAbstractConfigInfo();

    /**
     * 检查配置数据库中的对应的表中配置项是否存在
     */
    virtual bool Check_Config_Table();

    /**
     * 对需要升级的表中的列填入数据
     */
    virtual bool Upgrade_Config_Table_Data();


    static bool isEqual(const float &a, const float &b);
protected:
    virtual void lock();
    virtual void unlock();

    static std::string GBK2UTF8(std::string &str);

protected:
    QMutex m_mutex;
};

#endif // !defined(EA_5E46B88C_57C5_4c3e_80A1_B23EB043FC2C_INCLUDED_)
