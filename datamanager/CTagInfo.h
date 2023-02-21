#ifndef CTAGINFO_H
#define CTAGINFO_H

//标签信息
class CTagInfo {
public:
    CTagInfo();
    ~CTagInfo();

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

private:
    int m_iTagID{-1};
    int m_iMapID{-1};
    int m_iBattery{-1};
    int m_iPosX{0};
    int m_iPosY{0};
    int m_iPosZ{0};
    int m_iStaticTime{0};
};

#endif // CTAGINFO_H
