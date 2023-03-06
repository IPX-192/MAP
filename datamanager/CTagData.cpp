#include "CTagData.h"

CTagData::CTagData()
{
    m_iDataID = -1;
    m_iTagID = -1;
    m_iMapID = -1;
    m_iBattery = -1;
    m_iPosX = 0;
    m_iPosX = 0;
    m_iPosX = 0;
    m_iStaticTime = 0;
    m_strUserID = "";
    m_strUsername = "";
    m_strDepartment = "";
    m_strRole = "";
}

CTagData::~CTagData()
{

}

int CTagData::iTagID() const
{
    return m_iTagID;
}

void CTagData::setITagID(int iTagID)
{
    m_iTagID = iTagID;
}

int CTagData::iMapID() const
{
    return m_iMapID;
}

void CTagData::setIMapID(int iMapID)
{
    m_iMapID = iMapID;
}

int CTagData::iBattery() const
{
    return m_iBattery;
}

void CTagData::setIBattery(int iBattery)
{
    m_iBattery = iBattery;
}

int CTagData::iPosX() const
{
    return m_iPosX;
}

void CTagData::setIPosX(int iPosX)
{
    m_iPosX = iPosX;
}

int CTagData::iPosY() const
{
    return m_iPosY;
}

void CTagData::setIPosY(int iPosY)
{
    m_iPosY = iPosY;
}

int CTagData::iPosZ() const
{
    return m_iPosZ;
}

void CTagData::setIPosZ(int iPosZ)
{
    m_iPosZ = iPosZ;
}

int CTagData::iStaticTime() const
{
    return m_iStaticTime;
}

void CTagData::setIStaticTime(int iStaticTime)
{
    m_iStaticTime = iStaticTime;
}

string CTagData::strUserID() const
{
    return m_strUserID;
}

void CTagData::setStrUserID(const string &strUserID)
{
    m_strUserID = strUserID;
}

string CTagData::strUsername() const
{
    return m_strUsername;
}

void CTagData::setStrUsername(const string &strUsername)
{
    m_strUsername = strUsername;
}

string CTagData::strDepartment() const
{
    return m_strDepartment;
}

void CTagData::setStrDepartment(const string &strDepartment)
{
    m_strDepartment = strDepartment;
}

string CTagData::strRole() const
{
    return m_strRole;
}

void CTagData::setStrRole(const string &strRole)
{
    m_strRole = strRole;
}

int CTagData::iDataID() const
{
    return m_iDataID;
}

void CTagData::setIDataID(int iDataID)
{
    m_iDataID = iDataID;
}
