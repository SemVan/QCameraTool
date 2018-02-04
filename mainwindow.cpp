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

    processor = new ImageProcessor();

    initGrapicsOnWindow();

    qRegisterMetaType<cv::Mat>("cv::Mat");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::initGrapicsOnWindow() {
    ui->horizontalSlider->setMaximum(-1);
    ui->horizontalSlider->setMinimum(-15);
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
    ui->horizontalSlider->setValue(-6);
    tool->setExposure(-6);
}

void MainWindow::on_pushButton_clicked()
{
      cameraThread = new QThread();
      dispThread = new QThread();
      procThread = new QThread();

      disp = new displayer();
      disp->init(ui->graphicsView);




      QObject::connect(cameraThread, SIGNAL(started()), tool, SLOT(initTimer()));
      //QObject::connect(tool, SIGNAL(sendImage(QImage&)),disp,SLOT(showImage(QImage&)), Qt::BlockingQueuedConnection);
      QObject::connect(tool, SIGNAL(sendMat(cv::Mat)),processor,SLOT(fullOneFrameProcess(cv::Mat)));
      QObject::connect(processor, SIGNAL(sendImage(QImage&)),disp,SLOT(showImage(QImage&)), Qt::BlockingQueuedConnection);


      processor->moveToThread(procThread);
      //disp->moveToThread(dispThread);
      tool->moveToThread(cameraThread);
      procThread->start();
      cameraThread->start();

}


void MainWindow::sliderValueChanged(int value) {
    ui->label->setText(QString::number(value));
    tool->setExposure((double)value);
}


void MainWindow::on_pushButton_2_clicked()
{
    cv::Mat image;
    image = cv::imread("C:\\Coding\\kim.jpg");
    processor->fullOneFrameProcess(image);
}
