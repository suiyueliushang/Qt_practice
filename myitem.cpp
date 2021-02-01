#include "workarea.h"


//myItem::myItem(qreal x, qreal y, qreal w, qreal h, int t,QColor color,bool inWorkArea,QPen pen)
//{
//    this->x=x;
//    this->y=y;
//    this->width=w;
//    this->height=h;
//    this->paintType=t;
//    this->inWorkArea=inWorkArea;
//    this->pen=pen;
//    this->setAcceptedMouseButtons(Qt::LeftButton);
//    this->setAcceptDrops(false);
//    this->setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsMovable);
//    this->color=color;
//    setCursor(Qt::OpenHandCursor);

////    connect(this,&QGraphicsItem:)
//}
myItem::myItem(qreal w, qreal h, int t,QColor color,bool inWorkArea,QPen pen)
{
    this->width=w;
    this->height=h;
    this->paintType=t;
    this->inWorkArea=inWorkArea;
    this->pen=pen;
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setAcceptDrops(false);
    this->setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsMovable);
    this->color=color;
    setCursor(Qt::OpenHandCursor);

//    connect(this,&QGraphicsItem:)
}

QRectF myItem::boundingRect() const
{
//    qreal penWidth=0;
    return QRectF(0,0,this->width,this->height);
}

void myItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen();
    painter->setBrush(color);
    painter->setPen(pen);
    switch (paintType) {
    case 0://绘制矩形
        painter->drawRect(0,0,width,height);
        break;
    case 1://画⚪
        painter->drawEllipse(0,0,width,height);
        break;
    }
}

void myItem::setColor(QColor c)
{
    this->color=c;
    update();
}

QPoint myItem::getMidPos()
{
    return QPoint(x+width/2,y+height/2);
}

//void myItem::setPos(QPointF point)
//{
//    this->x=point.x();
//    this->y=point.y();
//}

void myItem::setPen(QPen & pen)
{
    this->pen=pen;
}

qreal myItem::getWidth()
{
    return this->width;
}

qreal myItem::getHeight()
{
    return this->height;
}

void myItem::setWorkArea(workArea *wa)
{
    this->wArea=wa;
}

void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
//    qDebug()<<this->pos();
//    qDebug()<<event->scenePos();
//    qDebug()<<"myItem mouse press event";
    if(this->zValue()>0){
        emit this->clicked();
    }

}

void myItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
    if(this->inWorkArea){///////////////////////////////
        //this->hide();
        this->wArea->currentMovedItem=this;
        emit this->moved();
        //this->setPos(event->scenePos());
    }
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);
    mime->setText(QString("%1 %2 %3 %4").arg(paintType).arg(width).arg(height).arg(int(inWorkArea)));
    mime->setColorData(QColor(this->color));
    QPixmap pixmap(this->width, this->height);
    pixmap.fill(QColor(255,255,255,20));
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.drawRect(0,0,this->width,this->height);
    switch (this->paintType) {
    case 0://绘制矩形
        painter.drawRect(0,0,width,height);
        break;
    case 1://画⚪
        painter.drawEllipse(0,0,width,height);
        break;
    }
    painter.end();

    pixmap.setMask(pixmap.createHeuristicMask());

    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(width/2, height/2));

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

void myItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    if(this->inWorkArea){
//        this->setPos(event->scenePos());
//        update();
//    }
    setCursor(Qt::OpenHandCursor);
}

void myItem::focusInEvent(QFocusEvent *event)
{
    if(this->inWorkArea){
        QPen pen(Qt::blue,2);
        this->setPen(pen);
        update();
    }
}

void myItem::focusOutEvent(QFocusEvent *event)
{
    if(this->inWorkArea){
        QPen pen(Qt::black,0);
        this->setPen(pen);
        update();
    }
}


//void myItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
//{
//    qDebug()<<"dragEnter";
//}

//void myItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
//{
//    qDebug()<<"drag leave";
//}

//void myItem::dropEvent(QGraphicsSceneDragDropEvent *event)
//{
//    if(event->mimeData()->hasText()){
//        QString str=event->mimeData()->text();
//        QStringList list= str.split(" ");
//        int width=qvariant_cast<int>(list[1]);
//        int height=qvariant_cast<int>(list[2]);
//        myItem * item=new myItem(event->pos().x()-width/2,event->pos().y()-height/2,width,height,qvariant_cast<int>(list[0]));
//        item->setParentItem(this);
//    }
//    qDebug()<<"drop";
//}



