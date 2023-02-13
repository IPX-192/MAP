#ifndef CUSERINFO_H
#define CUSERINFO_H

/*************************************************
  <类    名>    CUserInfo
  <功能描述>     用户信息类

  <作    者>    tcy
  <时    间>    2023-02-13
**************************************************/

#include <string>
using namespace std;

class CUserInfo
{
public:
    CUserInfo();
    virtual ~CUserInfo();

    string strUserID() const;
    void setStrUserID(const string &strUserID);

    string strUsername() const;
    void setStrUsername(const string &strUsername);

    string strDepartment() const;
    void setStrDepartment(const string &strDepartment);

    string strRole() const;
    void setStrRole(const string &strRole);

    int itagID() const;
    void setItagID(int itagID);

private:
    string m_strUserID;
    string m_strUsername;
    string m_strDepartment;
    string m_strRole;
    int    m_itagID;
};

#endif // CUSERINFO_H
