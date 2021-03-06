#include "displayer.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>


displayer::displayer(QObject *parent)
{

}


void displayer::init(QGraphicsView *v) {
    scene  = new QGraphicsScene();
    qDebug()<<"display init";
    view = v;
}


void displayer::showImage(QImage &imageToShow) {
    img = QPixmap::fromImage(imageToShow);
    shower();
}

void displayer::shower() {
    QRectF sceneRect = view->sceneRect();
    img.scaledToHeight(sceneRect.height());
    img.scaledToWidth(sceneRect.width());
    scene->clear();
    scene->addPixmap(img);
    view->setScene(scene);
    view->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}
