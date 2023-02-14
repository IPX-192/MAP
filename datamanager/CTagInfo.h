#ifndef CTAGINFO_H
#define CTAGINFO_H


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
    int m_iTagID;
    int m_iMapID;
    int m_iBattery;
    int m_iPosX;
    int m_iPosY;
    int m_iPosZ;
    int m_iStaticTime;
};

#endif // CTAGINFO_H
