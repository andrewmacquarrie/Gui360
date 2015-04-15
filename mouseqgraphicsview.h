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
    void drawScene();

    QStatusBar *statusBar;
    QString picFileName;
    int editing;

    QGraphicsScene *m_scene;

    QPoint cutStart;
    QPoint cutEnd;

    signals:
    void dataReady();

    public slots:
    void mousePressEvent(QMouseEvent * e);

    private:
    int m_click;
};


#endif // MOUSEQGRAPHICSVIEW

