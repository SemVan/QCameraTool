#include "cameratool.h"
#include <QDebug>

CameraTool::CameraTool(QObject *parent) : QObject(parent)
{

}


void CameraTool::startCamera() {
    for (int i=0;i<20;i++) {
        if(cam.open(i)) {
            break;
        }
    }
    cam.set(CV_CAP_PROP_AUTO_EXPOSURE, 0.0);
    cam.set(CV_CAP_PROP_EXPOSURE, -6.0);
    cam.set(CV_CAP_PROP_FPS, 60);
}

void CameraTool::convertMatToImage(cv::Mat &frame) {
    cv::Mat temp;
    cv::cvtColor(frame,temp,CV_BGR2RGB);
    image = QImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);;
    image = image.rgbSwapped();

}

QImage CameraTool::getImage(double exposure) {
    cam.read(img);
    cam.read(img);
    convertMatToImage(img);
}

void CameraTool::getImage() {
    cam.read(img);
    convertMatToImage(img);

}

void CameraTool::setExposure(double exposure) {
    cam.set(CV_CAP_PROP_EXPOSURE, exposure);
}

void CameraTool::timeOutHandler() {
    qDebug()<<"getting image";
    elTimer.start();
    getImage();
    qDebug()<<"image grabbed"<<elTimer.elapsed();
    elTimer.restart();
    sendImage(image);

}

void CameraTool::initTimer() {
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(timeOutHandler()));
    timer->setInterval(10);
    timer->start();
}


