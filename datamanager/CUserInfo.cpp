#include "CUserInfo.h"

CUserInfo::CUserInfo()
{
    m_strUserID = "";
    m_strUsername = "";
    m_strDepartment = "";
    m_strRole = "";
    m_itagID = -1;
}

CUserInfo::~CUserInfo()
{

}

string CUserInfo::strUserID() const
{
    return m_strUserID;
}

void CUserInfo::setStrUserID(const string &strUserID)
{
    m_strUserID = strUserID;
}

string CUserInfo::strUsername() const
{
    return m_strUsername;
}

void CUserInfo::setStrUsername(const string &strUsername)
{
    m_strUsername = strUsername;
}

string CUserInfo::strDepartment() const
{
    return m_strDepartment;
}

void CUserInfo::setStrDepartment(const string &strDepartment)
{
    m_strDepartment = strDepartment;
}

string CUserInfo::strRole() const
{
    return m_strRole;
}

void CUserInfo::setStrRole(const string &strRole)
{
    m_strRole = strRole;
}

int CUserInfo::itagID() const
{
    return m_itagID;
}

void CUserInfo::setItagID(int itagID)
{
    m_itagID = itagID;
}
