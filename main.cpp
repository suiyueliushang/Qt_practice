#include "mainwindow.h"
#include <QApplication>
#include <mygraphicsscene.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myGraphicsScene *scene=new myGraphicsScene();
    scene->setSceneRect(0,0,600,400);
    QGraphicsView view(scene);
    view.resize(620,420);
    view.show();
    return a.exec();
}
