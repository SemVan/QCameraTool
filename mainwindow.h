#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QMetaType>
#include <cameratool.h>
#include <displayer.h>
#include <imageprocessor.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void sliderValueChanged(int value);



    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    CameraTool *tool;
    ImageProcessor *processor;

    QThread *cameraThread;
    QThread *dispThread;
    QThread *procThread;
    displayer *disp;

    void initGrapicsOnWindow();
};

#endif // MAINWINDOW_H
