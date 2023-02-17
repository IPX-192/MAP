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
        QRect backImgRect( m_OriginX + m_vecCoordX.at(i) - 17,m_OriginY + m_vecCoordY.at(i) - 17,34,34);

        QImage backImg(":/iamge/coord.png");

        m_painter->drawImage(backImgRect, backImg);

        //图片下方绘制人员ID
        m_tagIDPen.setWidth(2);

        m_painter->drawText(backImgRect,Qt::AlignHCenter | Qt::AlignVCenter, QString::number(m_vecTagId.at(i)));
    }
}

void CUserCoordView::setCurCoord(int coordX, int coordY,int tagId)
{
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
