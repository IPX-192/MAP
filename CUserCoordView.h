#ifndef CUSERCOORDVIEW_H
#define CUSERCOORDVIEW_H


#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QVector>

class CUserCoordView : public QQuickPaintedItem
{
    Q_OBJECT
public:
    CUserCoordView();
    ~CUserCoordView();
    void paint(QPainter *painter);


    Q_INVOKABLE void drawCoordImage();


    Q_INVOKABLE void setCurCoord(int coordX, int coordY,int tagId);

    Q_INVOKABLE void setOriginCoord(int originX,int originY);

    Q_INVOKABLE void clearVecCoord();

private:
    QPainter *m_painter{nullptr};           //绘制指针

    QVector<int>   m_vecCoordX;             //缓存坐标X位置，单位是mm
    QVector<int>   m_vecCoordY;

    QVector<int>   m_vecTagId;
    QPen           m_tagIDPen;

    int            m_OriginX;
    int            m_OriginY;
    int            m_CoordImgWidth{24};
    int            m_CoordIdWidth{36};

};

#endif // CUSERCOORDVIEW_H
