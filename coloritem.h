#ifndef COLORITEM_H
#define COLORITEM_H

#include "include.h"

class ColorItem:public QGraphicsObject
{
    Q_OBJECT
public:
    ColorItem(int x,int y,int width,int height,QColor color);
    QColor getColor();
    QRectF boundingRect() const;
    void paint(QPainter * painter,const QStyleOptionGraphicsItem* option,QWidget* widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private:
    int x,y,width,height;
    QColor color;

};

#endif // COLORITEM_H
