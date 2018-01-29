#include "cameratool.h"
#include <QDebug>

CameraTool::CameraTool(QObject *parent) : QObject(parent)
{
    QObject::connect(&timer,SIGNAL(timeout()), this, SLOT(timeOutHandler()));
}


void CameraTool::startCamera() {
    for (int i=0;i<20;i++) {
        if(cam.open(i)) {
            break;
        }
    }
    cam.set(CV_CAP_PROP_AUTO_EXPOSURE, 0.0);
    cam.set(CV_CAP_PROP_EXPOSURE, -6.0);
    cam.set(CV_CAP_PROP_FPS, 30);
}

void CameraTool::convertMatToImage(cv::Mat frame) {
    cv::Mat temp;
    cv::cvtColor(frame,temp,CV_BGR2RGB);
    image = QImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);;
    image = image.rgbSwapped();

}

QImage CameraTool::getImage(double exposure) {
    //qDebug()<<cam.get(CV_CAP_PROP_EXPOSURE);
    cam.read(img);
    cam.read(img);
    convertMatToImage(img);
}

void CameraTool::getImage() {
    cam.read(img);
    qDebug()<<"image read";
    convertMatToImage(img);
    qDebug()<<"image converted";
}

void CameraTool::setExposure(double exposure) {
    cam.set(CV_CAP_PROP_EXPOSURE, exposure);
}

void CameraTool::timeOutHandler() {
    getImage();
    qDebug()<<"sending image";
    sendImage(image);
    qDebug()<<"image sent";
}

void CameraTool::initTimer() {
    timer.setInterval(100);
    timer.start();
}
