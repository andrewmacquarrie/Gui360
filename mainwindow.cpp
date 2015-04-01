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

void MainWindow::on_selectFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->fileNameTextbox->setText(tr("%1").arg(fileName));
}

void MainWindow::on_pushButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_startButton_clicked()
{
    QString fileName = ui->fileNameTextbox->toPlainText();

    char* cstr;
    std::string fname = fileName.toStdString();
    cstr = new char [fname.size()+1];
    strcpy( cstr, fname.c_str() );

    char fakeParam[] = "fake";
    //char fakeParam2[] = "/Users/drew/projects/SeamCut/bin/Debug/forest1.jpg";
    char *fakeargv[] = { fakeParam, cstr, NULL };
    int fakeargc = 2;

    seamcut(fakeargc, fakeargv);
}
