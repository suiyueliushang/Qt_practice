#ifndef MYITEM_H
#define MYITEM_H

#include "include.h"
class workArea;


class myItem : public QGraphicsObject
{
    Q_OBJECT
public:
    //(qreal x,qreal y,qreal width,qreal height,int t=0,QColor color=QColor(255,255,255,0),bool inWorkArea=false,QPen pen=QPen(Qt::black,0));
    myItem(qreal width,qreal height,int t=0,QColor color=QColor(255,255,255,150),bool inWorkArea=false,QPen pen=QPen(Qt::black,1));
    QRectF boundingRect() const;
    void paint(QPainter * painter,const QStyleOptionGraphicsItem* option,QWidget* widget);
    void setColor(QColor c);
    QPoint getMidPos();
    //void setPos(QPointF);
    void setPen(QPen &);
    qreal getWidth();
    qreal getHeight();
    void setWorkArea(workArea * wa);
    bool inWorkArea;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

//    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
//    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
//    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
signals:
    void clicked();
    void moved();
    void droped(QPointF);
public slots:

private:
    QPen pen;
    QColor color;
    int paintType;
    qreal x,y,width,height;
    workArea *wArea=NULL;
};

#endif // MYITEM_H
