#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include "include.h"
#include "myitem.h"
#include "workarea.h"
#include "coloritem.h"
class myGraphicsScene:public QGraphicsScene
{
    Q_OBJECT
public:
    myGraphicsScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void dragEnterEvent(QGraphicsSceneDragDropEvent*);
//    void dropEvent(QGraphicsSceneDragDropEvent *);
    myItem * currentClickedItem;
    workArea * WorkArea;
    bool isReady=false;
};

#endif // MYGRAPHICSSCENE_H
