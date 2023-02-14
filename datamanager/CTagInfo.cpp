#include "CTagInfo.h"

CTagInfo::CTagInfo()
{
    m_iTagID = -1;
    m_iMapID = -1;
    m_iBattery = -1;
    m_iPosX = 0;
    m_iPosX = 0;
    m_iPosX = 0;
    m_iStaticTime = 0;
}

CTagInfo::~CTagInfo()
{

}

int CTagInfo::iTagID() const
{
    return m_iTagID;
}

void CTagInfo::setITagID(int iTagID)
{
    m_iTagID = iTagID;
}

int CTagInfo::iMapID() const
{
    return m_iMapID;
}

void CTagInfo::setIMapID(int iMapID)
{
    m_iMapID = iMapID;
}

int CTagInfo::iBattery() const
{
    return m_iBattery;
}

void CTagInfo::setIBattery(int iBattery)
{
    m_iBattery = iBattery;
}

int CTagInfo::iPosX() const
{
    return m_iPosX;
}

void CTagInfo::setIPosX(int iPosX)
{
    m_iPosX = iPosX;
}

int CTagInfo::iPosY() const
{
    return m_iPosY;
}

void CTagInfo::setIPosY(int iPosY)
{
    m_iPosY = iPosY;
}

int CTagInfo::iPosZ() const
{
    return m_iPosZ;
}

void CTagInfo::setIPosZ(int iPosZ)
{
    m_iPosZ = iPosZ;
}

int CTagInfo::iStaticTime() const
{
    return m_iStaticTime;
}

void CTagInfo::setIStaticTime(int iStaticTime)
{
    m_iStaticTime = iStaticTime;
}
