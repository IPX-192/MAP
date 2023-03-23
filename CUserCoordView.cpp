#include "CUserCoordView.h"

CUserCoordView::CUserCoordView()
{

}

CUserCoordView::~CUserCoordView()
{

}

void CUserCoordView::paint(QPainter *painter)
{
    m_painter = painter;

    drawCoordImage();
}

void CUserCoordView::drawCoordImage()
{
    for(int i = 0;i<m_vecCoordX.size();i++)
    {
        //通常程序中Y轴坐标值是越往下越大,目前要更改为越往上越大，因此要取反值
        QRect backImgRect( m_OriginX + m_vecCoordX.at(i) - 12,100 - (m_OriginY + m_vecCoordY.at(i) + 12),m_CoordImgWidth,m_CoordImgWidth);
        QRect tagIDImgRect(m_OriginX + m_vecCoordX.at(i) - 18,100 - (m_OriginY + m_vecCoordY.at(i) - 5),m_CoordIdWidth,m_CoordImgWidth);
        QImage backImg(":/iamge/coord.png");

        m_painter->drawImage(backImgRect, backImg);

        //图片下方绘制人员ID
        m_tagIDPen.setWidth(2);

        m_painter->drawText(tagIDImgRect,Qt::AlignHCenter | Qt::AlignVCenter, QString::number(m_vecTagId.at(i)));
    }
}

void CUserCoordView::setCurCoord(int coordX, int coordY,int tagId)
{

    m_vecCoordX.append(coordX);
    m_vecCoordY.append(coordY);
    m_vecTagId.append(tagId);

    if(m_vecCoordX.size() == 4)
    {
        clearVecCoord();
        m_vecCoordX.append(coordX);
        m_vecCoordY.append(coordY);
        m_vecTagId.append(tagId);
        update();
    }
}

void CUserCoordView::setOriginCoord(int originX,int originY)
{
    m_OriginX = originX;
    m_OriginY = originY;
}

void CUserCoordView::clearVecCoord()
{
    m_vecCoordX.clear();
    m_vecCoordY.clear();
    m_vecTagId.clear();
    // update();
}
