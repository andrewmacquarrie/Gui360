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

public slots:
    void updateValues();

private slots:
    void on_pushButton_clicked();

    void on_startButton_clicked();

    void on_loadImageButton_clicked();

    void on_radioCutStart_clicked();

    void on_radioCutEnd_clicked();

private:
    Ui::MainWindow *ui;

    QString inputFileName;

    QGraphicsScene *scene;

};

#endif // MAINWINDOW_H
