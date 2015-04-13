#include "mouseqgraphicsview.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "mainwindow.h"

//MouseQGraphicsView::MouseQGraphicsView(QGraphicsScene *scene, QWidget *parent) :
//    QGraphicsView(parent),
//    m_scene(scene),
//    m_click(0)
//{
//    setScene(m_scene);
//}

MouseQGraphicsView::MouseQGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void MouseQGraphicsView::mousePressEvent(QMouseEvent * e)
{
    if(editing == "start") {
        cutStart = e->pos();
        //cutEnd = e->pos();
    } else if (editing == "end") {
        cutEnd = e->pos();
    }
    drawScene();
}

void MouseQGraphicsView::drawScene()
{
    QPixmap pic = QPixmap(picFileName);
    QSize imgHolderSize(size().width() - 2, size().height() - 2); // buffer needed or has scroll bar
    QPixmap scaledPic = pic.scaled(imgHolderSize,  Qt::KeepAspectRatio);
    m_scene->addPixmap(scaledPic);
    // scene->addText("bogotobogo.com", QFont("Arial", 20) );
    this->setScene(m_scene);

    QGraphicsRectItem* item1 = new QGraphicsRectItem(cutStart.x(),0,cutEnd.x() - cutStart.x(),scaledPic.height());
    item1->setBrush(QBrush(Qt::red));
    m_scene->addItem(item1);

//    if ( !m_click ) {
//        QGraphicsView::mousePressEvent(e);
//    }
}
