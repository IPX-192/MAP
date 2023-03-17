#include "COnlineTagInfo.h"

COnlineTagInfo::COnlineTagInfo()
{
    m_strUserID = "";
    m_strUsername = "";
    m_strDepartment = "";
    m_strRole = "";
    m_iTagID = -1;
    m_iMapID = -1;
    m_iBattery = -1;
    m_iPosX = 0;
    m_iPosX = 0;
    m_iPosX = 0;
    m_iStaticTime = 0;
}

COnlineTagInfo::~COnlineTagInfo()
{

}

int COnlineTagInfo::iTagID() const
{
    return m_iTagID;
}

void COnlineTagInfo::setITagID(int iTagID)
{
    m_iTagID = iTagID;
}

int COnlineTagInfo::iMapID() const
{
    return m_iMapID;
}

void COnlineTagInfo::setIMapID(int iMapID)
{
    m_iMapID = iMapID;
}

int COnlineTagInfo::iBattery() const
{
    return m_iBattery;
}

void COnlineTagInfo::setIBattery(int iBattery)
{
    m_iBattery = iBattery;
}

int COnlineTagInfo::iPosX() const
{
    return m_iPosX;
}

void COnlineTagInfo::setIPosX(int iPosX)
{
    m_iPosX = iPosX;
}

int COnlineTagInfo::iPosY() const
{
    return m_iPosY;
}

void COnlineTagInfo::setIPosY(int iPosY)
{
    m_iPosY = iPosY;
}

int COnlineTagInfo::iPosZ() const
{
    return m_iPosZ;
}

void COnlineTagInfo::setIPosZ(int iPosZ)
{
    m_iPosZ = iPosZ;
}

int COnlineTagInfo::iStaticTime() const
{
    return m_iStaticTime;
}

void COnlineTagInfo::setIStaticTime(int iStaticTime)
{
    m_iStaticTime = iStaticTime;
}

string COnlineTagInfo::strUserID() const
{
    return m_strUserID;
}

void COnlineTagInfo::setStrUserID(const string &strUserID)
{
    m_strUserID = strUserID;
}

string COnlineTagInfo::strUsername() const
{
    return m_strUsername;
}

void COnlineTagInfo::setStrUsername(const string &strUsername)
{
    m_strUsername = strUsername;
}

string COnlineTagInfo::strDepartment() const
{
    return m_strDepartment;
}

void COnlineTagInfo::setStrDepartment(const string &strDepartment)
{
    m_strDepartment = strDepartment;
}

string COnlineTagInfo::strRole() const
{
    return m_strRole;
}

void COnlineTagInfo::setStrRole(const string &strRole)
{
    m_strRole = strRole;
}

bool COnlineTagInfo::operator==(const COnlineTagInfo &info) const
{
    bool bEqual = (m_iTagID == info.m_iTagID) && (m_iPosX == info.m_iPosX) &&
                  (m_iPosY == info.m_iPosY) && (m_iPosZ == info.m_iPosZ) &&
                  (m_iStaticTime == info.m_iStaticTime) && (m_iBattery == info.iBattery());
    return bEqual;
}

COnlineTagInfo &COnlineTagInfo::operator=(const COnlineTagInfo &info)
{
    m_iTagID = info.iTagID();
    m_iPosX = info.iPosX();
    m_iPosY = info.iPosY();
    m_iPosZ = info.iPosZ();
    m_iStaticTime = info.iStaticTime();
    m_iBattery = info.iBattery();
    return *this;
}
