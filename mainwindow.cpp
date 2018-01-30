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

    initGrapicsOnWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::initGrapicsOnWindow() {
    ui->horizontalSlider->setMaximum(255);
    ui->horizontalSlider->setMinimum(0);
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
    ui->horizontalSlider->setValue(-6);
    tool->setExposure(-6);
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


void MainWindow::sliderValueChanged(int value) {
    ui->label->setText(QString::number(value));
    tool->setExposure((double)value);
}

