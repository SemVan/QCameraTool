#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QElapsedTimer>

class displayer : public QObject
{
    Q_OBJECT
public:
    explicit displayer(QObject *parent = 0);

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap img;
    void shower();
    QElapsedTimer timer;
public slots:
    void init(QGraphicsView *v);
    void showImage(QImage &imageToShow);



};

#endif // DISPLAYER_H
