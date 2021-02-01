#include "workarea.h"

workArea::workArea(int x, int y, int width, int height)
{
    this->dragOver=false;
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
    this->setAcceptDrops(true);
}

QRectF workArea::boundingRect() const
{
    qreal penWidth=2;
    return QRectF(x-penWidth/2,y-penWidth/2,width+penWidth,height+penWidth);
}

void workArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(dragOver ? QColor("#6babe5") : QColor("#5B9BD5"));
    painter->setPen(QPen(Qt::black,2));
    painter->drawRect(x,y,width,height);
}

void workArea::mousePressEvent(QMouseEvent *event)
{

}

void workArea::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"drag enter";
    event->accept();
    dragOver=true;
    update();
}

void workArea::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"drag leave";
    dragOver=false;
    update();
}

void workArea::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasText()){
        QString str=event->mimeData()->text();
        QStringList list= str.split(" ");
        int width=qvariant_cast<int>(list[1]);
        int height=qvariant_cast<int>(list[2]);
        bool isInWorkArea=qvariant_cast<bool>(list[3]);
        if(isInWorkArea && this->currentMovedItem &&this->currentMovedItem->inWorkArea){
            qDebug()<<"nei bu yi dong";
            this->currentMovedItem->moveBy(event->scenePos().x()-this->currentMovedItem->scenePos().x()-currentMovedItem->getWidth()/2,event->scenePos().y()-this->currentMovedItem->scenePos().y()-currentMovedItem->getHeight()/2);
            //this->currentMovedItem->setPos(event->scenePos());
            //this->currentMovedItem->update();
            emit this->currentMovedItem->droped(event->scenePos());
            return;
        }
        qDebug()<<"wai bu yi dong";
        myItem* item=new myItem(width,height,qvariant_cast<int>(list[0]),qvariant_cast<QColor>(event->mimeData()->colorData()),true);
        parentScene->addItem(item);
        qDebug()<<"yi jian li xin item";
        qDebug()<<event->scenePos();
        qDebug()<<width;
        qDebug()<<height;
        item->setPos(event->scenePos().x()-width/2,event->scenePos().y()-height/2);
        qDebug()<<item->pos();
        item->setWorkArea(this);
//        item->setParentItem(this);
        item->setZValue(1);
//        connect(item,&myItem::clicked,this,[=](){//完成连线工作，完成ready工作
//            //item->setFocus(Qt::MouseFocusReason);
//            //qDebug()<<"setFocus item";
//            //parentScene->isReady==true;
//            this->isClickItem=true;
//            this->clickedItem=item;
//        });
        dragOver=false;
        qDebug()<<"dragOver=false";
    }
    update();
     qDebug()<<scene()->items().count();
}
