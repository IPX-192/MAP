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

    qDebug()<<"看看原点位置" << m_OriginY;
    for(int i = 0;i<m_vecCoordX.size();i++)
    {
        QRect backImgRect( m_OriginX + m_vecCoordX.at(i) - 12,m_OriginY + m_vecCoordY.at(i) - 12,m_CoordImgWidth,m_CoordImgWidth);
        QRect tagIDImgRect(m_OriginX + m_vecCoordX.at(i) - 18,m_OriginY + m_vecCoordY.at(i) + 2,m_CoordIdWidth,m_CoordImgWidth);
        QImage backImg(":/iamge/coord.png");

        m_painter->drawImage(backImgRect, backImg);

        //图片下方绘制人员ID
        m_tagIDPen.setWidth(2);

        m_painter->drawText(tagIDImgRect,Qt::AlignHCenter | Qt::AlignVCenter, QString::number(m_vecTagId.at(i)));
    }
}

void CUserCoordView::setCurCoord(int coordX, int coordY,int tagId)
{
    qDebug()<<"看看设置的Y" << coordY;
    m_vecCoordX.append(coordX);
    m_vecCoordY.append(coordY);
    m_vecTagId.append(tagId);
    update();
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
    update();
}
