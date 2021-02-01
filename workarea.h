#ifndef WORKAREA_H
#define WORKAREA_H
#include "include.h"
#include "myitem.h"
class workArea: public QGraphicsObject
{
    Q_OBJECT
public:
    workArea(int x,int y,int width,int height);

    QRectF boundingRect() const;
    void paint(QPainter * painter,const QStyleOptionGraphicsItem* option,QWidget* widget);

    void mousePressEvent(QMouseEvent *);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    //myItem * currentClickedItem;
    QGraphicsScene * parentScene;

    bool isClickItem=false;
    myItem *clickedItem=NULL;
    myItem * currentMovedItem=NULL;
signals:
private:
    bool dragOver;
    int x,y,width,height;

};

#endif // WORKAREA_H
