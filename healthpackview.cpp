#include "healthpackview.h"
#include <iostream>

extern int SCALE;

HealthPackView::HealthPackView()
{
    setPixmap(QPixmap(":/image/healthpack.png"));
    scaleItem(SCALE);
}

void HealthPackView::scaleItem(double scale)
{
    double size=scale/50;
    QGraphicsPixmapItem::setScale(size);
}

void HealthPackView::used_slot()
{
    this->hide();
}

void HealthPackView::setPos(int newX, int newY)
{
    QGraphicsPixmapItem::setPos(newX*SCALE, newY*SCALE);
}
