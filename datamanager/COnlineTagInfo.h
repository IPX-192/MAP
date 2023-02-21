#ifndef CONLINETAGINFO_H
#define CONLINETAGINFO_H

#include <string>
using namespace std;

//在线标签信息
class COnlineTagInfo {
public:
    COnlineTagInfo();
    ~COnlineTagInfo();

    int iTagID() const;
    void setITagID(int iTagID);

    int iMapID() const;
    void setIMapID(int iMapID);

    int iBattery() const;
    void setIBattery(int iBattery);

    int iPosX() const;
    void setIPosX(int iPosX);

    int iPosY() const;
    void setIPosY(int iPosY);

    int iPosZ() const;
    void setIPosZ(int iPosZ);

    int iStaticTime() const;
    void setIStaticTime(int iStaticTime);

    string strUserID() const;
    void setStrUserID(const string &strUserID);

    string strUsername() const;
    void setStrUsername(const string &strUsername);

    string strDepartment() const;
    void setStrDepartment(const string &strDepartment);

    string strRole() const;
    void setStrRole(const string &strRole);

private:
    string m_strUserID{""};
    string m_strUsername{""};
    string m_strDepartment{""};
    string m_strRole{""};
    int m_iTagID{-1};
    int m_iMapID{-1};
    int m_iBattery{-1};
    int m_iPosX{0};
    int m_iPosY{0};
    int m_iPosZ{0};
    int m_iStaticTime{0};
};

#endif // CONLINETAGINFO_H
