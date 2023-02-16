#ifndef CUSERCOORDVIEW_H
#define CUSERCOORDVIEW_H


#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPainter>
#include <QPen>

class CUserCoordView : public QQuickPaintedItem
{
    Q_OBJECT
public:
    CUserCoordView();
    ~CUserCoordView();
    void paint(QPainter *painter);

};

#endif // CUSERCOORDVIEW_H
