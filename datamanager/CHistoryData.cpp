#include "CHistoryData.h"

CHistoryData::CHistoryData()
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

CHistoryData::~CHistoryData()
{

}

int CHistoryData::iTagID() const
{
    return m_iTagID;
}

void CHistoryData::setITagID(int iTagID)
{
    m_iTagID = iTagID;
}

int CHistoryData::iMapID() const
{
    return m_iMapID;
}

void CHistoryData::setIMapID(int iMapID)
{
    m_iMapID = iMapID;
}

int CHistoryData::iBattery() const
{
    return m_iBattery;
}

void CHistoryData::setIBattery(int iBattery)
{
    m_iBattery = iBattery;
}

int CHistoryData::iPosX() const
{
    return m_iPosX;
}

void CHistoryData::setIPosX(int iPosX)
{
    m_iPosX = iPosX;
}

int CHistoryData::iPosY() const
{
    return m_iPosY;
}

void CHistoryData::setIPosY(int iPosY)
{
    m_iPosY = iPosY;
}

int CHistoryData::iPosZ() const
{
    return m_iPosZ;
}

void CHistoryData::setIPosZ(int iPosZ)
{
    m_iPosZ = iPosZ;
}

int CHistoryData::iStaticTime() const
{
    return m_iStaticTime;
}

void CHistoryData::setIStaticTime(int iStaticTime)
{
    m_iStaticTime = iStaticTime;
}

string CHistoryData::strUserID() const
{
    return m_strUserID;
}

void CHistoryData::setStrUserID(const string &strUserID)
{
    m_strUserID = strUserID;
}

string CHistoryData::strUsername() const
{
    return m_strUsername;
}

void CHistoryData::setStrUsername(const string &strUsername)
{
    m_strUsername = strUsername;
}

string CHistoryData::strDepartment() const
{
    return m_strDepartment;
}

void CHistoryData::setStrDepartment(const string &strDepartment)
{
    m_strDepartment = strDepartment;
}

string CHistoryData::strRole() const
{
    return m_strRole;
}

void CHistoryData::setStrRole(const string &strRole)
{
    m_strRole = strRole;
}

int CHistoryData::iDataID() const
{
    return m_iDataID;
}

void CHistoryData::setIDataID(int iDataID)
{
    m_iDataID = iDataID;
}
