#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <cameratool.h>
#include <displayer.h>


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
    void showImage();
    void sliderValueChanged(int value);
    void timeOutHandler();
    void saveImage(QImage image);

private:
    Ui::MainWindow *ui;
    CameraTool *tool;
    QGraphicsScene *scene;
    QTimer timer;
    QPixmap img;
    QImage imageToShow;
    QThread *cameraThread;
    QThread *dispThread;
    displayer *disp;

    void initGrapicsOnWindow();
};

#endif // MAINWINDOW_H
