#include "CMapOriginInfo.h"

CMapOriginInfo::CMapOriginInfo()
{
    m_iPosX = 0;
    m_iPosY = 0;
    m_iPosZ = 0;
}

int CMapOriginInfo::iPosX() const
{
    return m_iPosX;
}

void CMapOriginInfo::setIPosX(int iPosX)
{
    m_iPosX = iPosX;
}

int CMapOriginInfo::iPosY() const
{
    return m_iPosY;
}

void CMapOriginInfo::setIPosY(int iPosY)
{
    m_iPosY = iPosY;
}

int CMapOriginInfo::iPosZ() const
{
    return m_iPosZ;
}

void CMapOriginInfo::setIPosZ(int iPosZ)
{
    m_iPosZ = iPosZ;
}
