#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tool = new CameraTool();
    tool->startCamera();
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(timeOutHandler()));

    initGrapicsOnWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::initGrapicsOnWindow() {
    ui->horizontalSlider->setMaximum(-1);
    ui->horizontalSlider->setMinimum(-15);
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
    ui->horizontalSlider->setValue(-1);
    tool->setExposure(-1);
    scene = new QGraphicsScene();
}

void MainWindow::on_pushButton_clicked()
{
      cameraThread = new QThread();
      dispThread = new QThread();
      disp = new displayer();
      disp->init(ui->graphicsView);

      QObject::connect(cameraThread, SIGNAL(started()), tool, SLOT(initTimer()));
      QObject::connect(tool, SIGNAL(sendImage(QImage&)),disp,SLOT(showImage(QImage&)), Qt::BlockingQueuedConnection);

      tool->moveToThread(cameraThread);
      cameraThread->start();

}


void MainWindow::showImage() {
    img = QPixmap::fromImage(imageToShow);
    QRectF sceneRect = ui->graphicsView->sceneRect();
    img.scaledToHeight(sceneRect.height());
    img.scaledToWidth(sceneRect.width());
    scene->addPixmap(img);
    //scene->setSceneRect(img.rect());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);


}


void MainWindow::sliderValueChanged(int value) {
    ui->label->setText(QString::number(value));
    tool->setExposure((double)value);
}


void MainWindow::timeOutHandler() {
    showImage();
}


void MainWindow::saveImage(QImage image) {

    imageToShow = image;
    qDebug()<<"image saved";
    timer.start(10);
}
