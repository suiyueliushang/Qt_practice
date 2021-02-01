#include "coloritem.h"


ColorItem::ColorItem(int x, int y, int width, int height, QColor color)
{
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
    this->color=color;
}

QColor ColorItem::getColor()
{
    return color;
}

QRectF ColorItem::boundingRect() const
{
    qreal penWidth=0;
    return QRectF(x-penWidth/2,y-penWidth/2,width+penWidth,height+penWidth);
}

void ColorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(color);
    painter->drawRect(x,y,width,height);
}

void ColorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit this->clicked();
    qDebug()<<"color item clicked";
}
