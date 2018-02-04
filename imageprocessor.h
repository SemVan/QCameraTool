#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <QVector>
#include <QObject>

class ImageProcessor: public QObject
{
    Q_OBJECT

public:
    ImageProcessor();
    QVector<double> plety;
    cv::Mat findSkinRegions(cv::Mat& frame);
    bool isface;
    int face_x;
    int face_y;
    int face_r;

public slots:
    void fullOneFrameProcess(cv::Mat frame);


signals:
    void faceIsReade(cv::Mat face);
    void sendImage(QImage &image);
    void numberIsReady(double intence);

private:
   // cv::VideoCapture camera;
    cv::CascadeClassifier faceHaarCascade;


    void detectFace(cv::Mat &frame);

    cv::Mat filterSkinMask(cv::Mat& mask);
    QVector<double> calculateAverage(cv::Mat& frame);
    void convertMatToImage(cv::Mat &frame);








};

#endif // IMAGEPROCESSOR_H
