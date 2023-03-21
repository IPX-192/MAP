#ifndef CDEVINFO_H
#define CDEVINFO_H

#include <string>
using namespace std;

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

    bool bHighlight() const;
    void setBHighlight(bool bHighlight);

    bool operator==(const CDevInfo& other) const;

    int iDevWidth() const;
    void setIDevWidth(int iDevWidth);

private:
    int m_iDevID{-1};
    string m_strDevName{""};
    int m_iDevPos{-1};
    int m_iDevWidth{0};
    bool m_bHighlight{false};
};

#endif // CDEVINFO_H
