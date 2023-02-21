#ifndef CMAPORIGININFO_H
#define CMAPORIGININFO_H

//原点配置信息类
class CMapOriginInfo {
public:
    CMapOriginInfo();
    ~CMapOriginInfo();

    int iPosX() const;
    void setIPosX(int iPosX);

    int iPosY() const;
    void setIPosY(int iPosY);

    int iPosZ() const;
    void setIPosZ(int iPosZ);

private:
    int m_iPosX;
    int m_iPosY;
    int m_iPosZ;
};

#endif // CMAPORIGININFO_H
