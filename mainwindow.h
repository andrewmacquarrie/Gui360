#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_selectFileButton_clicked();

    void on_startButton_clicked();

    void on_loadImageButton_clicked();

private:
    Ui::MainWindow *ui;


    QGraphicsScene *scene;

};

#endif // MAINWINDOW_H
