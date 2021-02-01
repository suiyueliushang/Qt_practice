#include "mygraphicsscene.h"

myGraphicsScene::myGraphicsScene()
{
    this->setBackgroundBrush(QColor("#5B9BD5"));
    myItem * rect1=new myItem(40,40);
    this->addItem(rect1);
    rect1->moveBy(40,140);
    rect1->setAcceptDrops(true);
    myItem * circle =new myItem(40,40,1);
    this->addItem(circle);
    circle->moveBy(40,250);

    ColorItem *colorItem[4];

    colorItem[0]=new ColorItem(150,40,80,30,QColor("#D9D9D9"));
    colorItem[1]=new ColorItem(250,40,80,30,QColor("#7F7F7F"));
    colorItem[2]=new ColorItem(350,40,80,30,QColor("#595959"));
    colorItem[3]=new ColorItem(450,40,80,30,QColor("#F8CBAD"));
    this->addItem(colorItem[0]);
    this->addItem(colorItem[1]);
    this->addItem(colorItem[2]);
    this->addItem(colorItem[3]);


    WorkArea=new workArea(130,100,440,270);
    this->addItem(WorkArea);
    WorkArea->parentScene=this;
    for(int i=0;i<4;i++)
        connect(colorItem[i],&ColorItem::clicked,this,[=](){
            if(this->isReady){
                this->currentClickedItem->setColor(colorItem[i]->getColor());
                this->currentClickedItem->update();
            }
        });

}

void myGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //先判断点击位置，在判断当前状态
    QGraphicsItem * item=this->itemAt(event->scenePos(),QTransform());
    if(!item){//没点到
        qDebug()<<"mei dian dao";
        isReady=false;
        currentClickedItem=0;
        return ;
    }
    else{
        qDebug()<<event->scenePos();
        qDebug()<<item->scenePos();
        if(item->zValue()==0){
            if(event->scenePos().y()<=70 && event->scenePos().y()>=30){
                qDebug()<<"dian dao yan se";
                return QGraphicsScene::mousePressEvent(event);
            }
            else{
                qDebug()<<"dian dao qi ta";
                isReady=false;
                currentClickedItem=0;
            }
        }
        else{//点到
            if(!isReady){
                qDebug()<<"dian dao dan is not ready";
                isReady=true;
                //this->setFocusItem(item);
                currentClickedItem=static_cast<myItem*>(item);
            }
            else{//连线
                qDebug()<<"lian xian";
                qDebug()<<item->pos();
                myItem *thisItem=static_cast<myItem*>(item);
                QGraphicsLineItem* line=new QGraphicsLineItem(currentClickedItem->scenePos().x()+currentClickedItem->getWidth()/2,
                                                              currentClickedItem->scenePos().y()+currentClickedItem->getHeight()/2,
                                                              thisItem->scenePos().x()+thisItem->getWidth()/2,
                                                              thisItem->scenePos().y()+thisItem->getHeight()/2);
                this->addItem(line);
                line->setZValue(0.5);
                connect(thisItem,&myItem::moved,[=](){
                    line->hide();
                });
                connect(currentClickedItem,&myItem::moved,[=](){
                    line->hide();
                });
                myItem* left=currentClickedItem;
                myItem* right=thisItem;
                connect(thisItem,&myItem::droped,[=](QPointF point){
                    line->setLine(left->scenePos().x()+left->getWidth()/2,
                                  left->scenePos().y()+left->getHeight()/2,
                                  point.x(),point.y());
                    line->show();
                });
                connect(currentClickedItem,&myItem::droped,[=](QPointF point){
                    line->setLine(point.x(),point.y(),right->scenePos().x()+right->getWidth()/2,
                                  right->scenePos().y()+right->getHeight()/2);
                    line->show();
                });
                isReady=false;
                //this->setFocusItem(item);
                currentClickedItem=0;
            }
        }
        return QGraphicsScene::mousePressEvent(event);
}

//////////////////////////////////////////////////////////////////
//        if(item && item->zValue()>0){
//            isReady=true;
//            //this->setFocusItem(item);
//            currentClickedItem=static_cast<myItem*>(item);
//        }
//        else{
//            qDebug()<<"ready false";
//            isReady=false;
//            this->clearFocus();
//            currentClickedItem=0;
//        }
///////////////////////////////////////////////////////////////////

}

void myGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton){
        qDebug()<<"mouse move";
        this->isReady=false;
        this->currentClickedItem=0;
    }
    return QGraphicsScene::mouseMoveEvent(event);

}

////////////////////////////////////////////////////////////////////////////////////////
//void myGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    if(this->itemAt(event->pos(),QTransform())!=NULL){
//        QGraphicsItem *item=this->itemAt(event->pos(),QTransform());
//        int i=0;
//        for(;i<WorkArea->childItems().length()&&item!=WorkArea->childItems()[i];i++);
//        if(i<WorkArea->childItems().length())
//            this->currentClickedItem=item;
//        else this->currentClickedItem=NULL;
//    }
//    else{
//        this->currentClickedItem=NULL;
//    }

//}
///////////////////////////////////////////////////////////////////////////////////////
//void myGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *e)
//{

//}

//void myGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *e)
//{

//}

