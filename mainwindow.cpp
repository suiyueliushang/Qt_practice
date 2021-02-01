#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myitem.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setBackgroundBrush(QColor("#5B9BD5"));
    QGraphicsScene *scene=new QGraphicsScene();
    scene->setParent(this);
    scene->setSceneRect(0,0,600,400);
    scene->setBackgroundBrush(QColor("#5B9BD5"));
    QGraphicsRectItem * rect1=new QGraphicsRectItem(40,140,40,40);
    scene->addItem(rect1);
    QGraphicsEllipseItem * circle =new QGraphicsEllipseItem(40,250,40,40);
    scene->addItem(circle);

    QGraphicsRectItem *color1=new QGraphicsRectItem(150,40,80,30);
    QGraphicsRectItem *color2=new QGraphicsRectItem(250,40,80,30);
    QGraphicsRectItem *color3=new QGraphicsRectItem(350,40,80,30);
    QGraphicsRectItem *color4=new QGraphicsRectItem(450,40,80,30);
    color1->setBrush(QColor("#D9D9D9"));
    color2->setBrush(QColor("#7F7F7F"));
    color3->setBrush(QColor("#595959"));
    color4->setBrush(QColor("#F8CBAD"));
    scene->addItem(color1);
    scene->addItem(color2);
    scene->addItem(color3);
    scene->addItem(color4);

    QGraphicsRectItem * WorkArea=new QGraphicsRectItem(130,100,440,270);
    scene->addItem(WorkArea);

    QGraphicsView *view1=new QGraphicsView(scene);
    view1->resize(620,420);
    view1->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
