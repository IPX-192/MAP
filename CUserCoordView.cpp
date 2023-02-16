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
        QRect backImgRect(m_vecCoordX.at(i),m_vecCoordY.at(i),34,34);

        QImage backImg(":/iamge/coord.png");

        m_painter->drawImage(backImgRect, backImg);
    }


}

void CUserCoordView::setCurCoord(int coordX, int coordY)
{
    m_vecCoordX.append(coordX);
    m_vecCoordY.append(coordY);
    update();
}
