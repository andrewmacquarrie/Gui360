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
    int xPos = e->x();
    int yPos = e->y();

    this->statusBar->showMessage(QString("Mouse move (%1,%2)").arg(xPos).arg(yPos));

//    if ( !m_click ) {
//        QGraphicsView::mousePressEvent(e);
//    }
}
