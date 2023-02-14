///////////////////////////////////////////////////////////
//  CAbstractConfigInfo.cpp
//  Implementation of the Class CAbstractConfigInfo
//  Created on:      29-十一月-2016 14:22:22
//  Original author: ZHY
///////////////////////////////////////////////////////////
#include "CAbstractConfigInfo.h"
#include <cmath>
#include <QString>

CAbstractConfigInfo::CAbstractConfigInfo()
{
}

CAbstractConfigInfo::~CAbstractConfigInfo()
{

}

bool CAbstractConfigInfo::Check_Config_Table()
{
    return true;
}

bool CAbstractConfigInfo::Upgrade_Config_Table_Data()
{
    return true;
}

bool CAbstractConfigInfo::isEqual(const float &a, const float &b)
{
    return fabs(a - b) < 0.0000001;
}

void CAbstractConfigInfo::lock()
{
    m_mutex.lock();
}

void CAbstractConfigInfo::unlock()
{
    m_mutex.unlock();
}

string CAbstractConfigInfo::GBK2UTF8(string &str)
{
    QString temp = QString::fromLocal8Bit(str.c_str());
    std::string ret = temp.toUtf8().data();
    return ret;
}
