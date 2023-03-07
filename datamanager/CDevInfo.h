#ifndef CDEVINFO_H
#define CDEVINFO_H

#include <string>
using namespace std;

//设备信息
class CDevInfo {
public:
    CDevInfo();
    ~CDevInfo();

    int iDevID() const;
    void setIDevID(int iDevID);

    string strDevName() const;
    void setStrDevName(const string &strDevName);

    int iDevPos() const;
    void setIDevPos(int iDevPos);

private:
    int m_iDevID{-1};
    string m_strDevName{""};
    int m_iDevPos{-1};
};

#endif // CDEVINFO_H
