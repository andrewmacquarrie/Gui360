#ifndef MOUSEQGRAPHICSVIEW
#define MOUSEQGRAPHICSVIEW

#include <QMainWindow>

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class MouseQGraphicsView : public QGraphicsView
{
    Q_OBJECT
    public:
    //MouseQGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
    MouseQGraphicsView(QWidget *parent = 0);
    QStatusBar *statusBar;


    public slots:
    void mousePressEvent(QMouseEvent * e);

    private:
    QGraphicsScene *m_scene;
    int m_click;
};


#endif // MOUSEQGRAPHICSVIEW

