#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "seamcut.h"
#include "editingmode.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MouseQGraphicsView* view = ui->graphicsView;

    view->statusBar = this->statusBar();
    view->m_scene = new QGraphicsScene(this);
    view->editing = EditingMode::cutStart;
    connect(view, SIGNAL(dataReady()), this, SLOT(updateValues()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_startButton_clicked()
{
    std::string outputFilename = ui->outputFilenameEdit->toPlainText().toStdString();

    std::string cutSize = ui->cutSizeEdit->toPlainText().toStdString();
    std::string overlapSize = ui->cutSizeEdit->toPlainText().toStdString();
    std::string leeway = ui->leewayEdit->toPlainText().toStdString();
    std::string cutStart = ui->cutStartEdit->toPlainText().toStdString();

    seamcut(inputFileName.toStdString(), outputFilename, stoi(cutSize), stoi(overlapSize), stoi(leeway), stoi(cutStart));
}

void MainWindow::on_loadImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->graphicsView->picFileName = fileName;
    ui->graphicsView->drawScene();
    inputFileName = fileName;
}

void MainWindow::on_radioCutStart_clicked()
{
    ui->graphicsView->editing = EditingMode::cutStart;
}

void MainWindow::on_radioCutEnd_clicked()
{
    ui->graphicsView->editing = EditingMode::cutEnd;
}

void MainWindow::updateValues()
{
    int xStart = ui->graphicsView->cutStart.x();
    int xEnd = ui->graphicsView->cutEnd.x();

    int cutSize = xEnd - xStart;

    if(cutSize < 1) {
        return;
    }

    double fraction = (double) cutSize / (double) ui->graphicsView->width();
    QPixmap pic = QPixmap(inputFileName); // TODO: this is rubbsih. Should store img size
    double cutSizeInImageTerms = ((double )pic.size().width()) * fraction;
    QString asStr = QString::fromStdString(std::to_string((int) cutSizeInImageTerms));
    ui->cutSizeEdit->clear();
    ui->cutSizeEdit->insertPlainText(asStr);

    double startFraction = (double) xStart / (double) ui->graphicsView->width();
    double cutStartInImageTerms = ((double )pic.size().width()) * startFraction;
    ui->cutStartEdit->clear();
    ui->cutStartEdit->insertPlainText(QString::fromStdString(std::to_string((int) cutStartInImageTerms)));
}
