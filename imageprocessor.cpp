#include "imageprocessor.h"
#include "QMessageBox"
#include <QDebug>
#include <QElapsedTimer>

#define MINIMUM_FACE_SIZE 250

ImageProcessor::ImageProcessor()
{
    isface = 0;
    faceHaarCascade.load("C:///Coding///Cascades//haarcascade_frontalface_alt.xml");

}


void ImageProcessor::fullOneFrameProcess(cv::Mat frame) {
    detectFace(frame);
}

void ImageProcessor::detectFace(cv::Mat &frame) {
    calculateAverage(frame);
    QElapsedTimer elTimer;
    elTimer.start();
    cv::Mat face;
    std::vector<cv::Rect> faces;

    if (faceHaarCascade.empty()) {
        isface=0;
        return;
    }

    faceHaarCascade.detectMultiScale( frame, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(MINIMUM_FACE_SIZE, MINIMUM_FACE_SIZE) );

    if (faces.size()) {
        face_x = faces[0].x;
        face_y = faces[0].y;
        face_r = faces[0].width;
        face = frame(faces[0]);
        face = findSkinRegions(face);
        cv::Point center( faces[0].x + faces[0].width*0.5, faces[0].y + faces[0].height*0.5 );
        cv::ellipse( frame, center, cv::Size( faces[0].width*0.5, faces[0].height*0.5), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
     } else {
        face = frame;
        qDebug()<<"no face";
    }

    qDebug()<<"full frame procedure"<<elTimer.elapsed();
    convertMatToImage(face);
}

cv::Mat ImageProcessor::findSkinRegions(cv::Mat& frame) {

    int lowH=0;
    int lowS=58;
    int lowV=0;

    int highH=25;
    int highS=173;
    int highV=255;

    int lowR = 95;
    int lowG = 40;
    int lowB = 20;


    cv::Mat hsvConverted;
    cv::cvtColor(frame,hsvConverted,CV_BGR2HSV);

    cv::Mat skinMaskHsv;
    cv::inRange(hsvConverted, cv::Scalar(lowH, lowS, lowV),cv::Scalar(highH, highS, highV), skinMaskHsv);


    cv::Mat colors[4];
    cv::Mat argbConverted;
    cv::cvtColor(frame, argbConverted, CV_BGR2RGBA);
    cv::split(argbConverted, colors);

    cv::Mat skinMaskRgb(colors[0].rows, colors[0].cols, colors[0].type());

    for (int i=0; i<colors[0].rows; i++) {
        for (int j=0; j<colors[0].cols;j++) {
            int r = (int)colors[0].at<uchar>(i,j);
            int g = (int)colors[1].at<uchar>(i,j);
            int b = (int)colors[2].at<uchar>(i,j);
            int a = (int)colors[3].at<uchar>(i,j);

            if (r>lowR && g>lowG && b>lowB && r>g && r>b && (r-g)>15 && a>15) {
                skinMaskRgb.at<uchar>(i, j) = 255;
            } else {
                skinMaskRgb.at<uchar>(i, j) = 0;
            }

        }
    }



    cv::Mat skinMask;
    cv::bitwise_and(skinMaskHsv, skinMaskRgb, skinMask);

    skinMask = filterSkinMask(skinMask);
    cv::Mat finalImage;
    frame.copyTo(finalImage,skinMask);
    return finalImage;

}


cv::Mat ImageProcessor::filterSkinMask(cv::Mat& mask) {
    cv::Mat newMask;
    cv::Mat kernel=cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11,11));
    cv::erode(mask,newMask,kernel);
    cv::dilate(newMask,newMask,kernel);
    return newMask;
}

QVector<double> ImageProcessor::calculateAverage(cv::Mat& frame) {
    cv::Scalar means = cv::mean(frame);
    QVector<double> results;
    results.append(means[0]);
    results.append(means[1]);
    results.append(means[2]);
    return results;

}


void ImageProcessor::convertMatToImage(cv::Mat &frame) {
    cv::Mat temp;
    cv::cvtColor(frame,temp,CV_BGR2RGB);
    QImage image = QImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);;
    image = image.rgbSwapped();
    sendImage(image);
}
