#include "CDevInfo.h"

CDevInfo::CDevInfo()
{
    m_iDevID = -1;
    m_strDevName = "";
    m_iDevPos = -1;
}

CDevInfo::~CDevInfo()
{

}

int CDevInfo::iDevID() const
{
    return m_iDevID;
}

void CDevInfo::setIDevID(int iDevID)
{
    m_iDevID = iDevID;
}

string CDevInfo::strDevName() const
{
    return m_strDevName;
}

void CDevInfo::setStrDevName(const string &strDevName)
{
    m_strDevName = strDevName;
}

int CDevInfo::iDevPos() const
{
    return m_iDevPos;
}

void CDevInfo::setIDevPos(int iDevPos)
{
    m_iDevPos = iDevPos;
}
