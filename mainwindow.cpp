#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "seamcut.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Image Files (*.png *.jpg *.bmp)"));

    char fakeParam[] = "fake";
    char fakeParam2[] = "/Users/drew/projects/SeamCut/bin/Debug/forest1.jpg";
    char *fakeargv[] = { fakeParam, fakeParam2, NULL };
    int fakeargc = 2;
    seamcut(fakeargc, fakeargv);

    qApp->quit();
}

