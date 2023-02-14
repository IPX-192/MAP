#ifndef CMAPORIGINCONFIG_H
#define CMAPORIGINCONFIG_H

/*************************************************
  <类    名>    CMapOriginConfig
  <功能描述>     地图配置

  <作    者>    tcy
  <时    间>    2023-02-13
**************************************************/

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

#endif // CMAPORIGINCONFIG_H
