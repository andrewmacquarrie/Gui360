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
    std::string inputFileName = ui->fileNameTextbox->toPlainText().toStdString();
    std::string outputFilename = ui->outputFilenameEdit->toPlainText().toStdString();

    std::string cutSize = ui->cutSizeEdit->toPlainText().toStdString();
    std::string overlapSize = ui->cutSizeEdit->toPlainText().toStdString();
    std::string leeway = ui->leewayEdit->toPlainText().toStdString();

    seamcut(inputFileName, outputFilename, stoi(cutSize), stoi(overlapSize), stoi(leeway));
}
