#include "penemyview.h"

extern int SCALE;

PEnemyView::PEnemyView()
{
    setPixmap(QPixmap(":/image/penemy.png"));
    PEnemyView::scaleItem(SCALE);
}

void PEnemyView::scaleItem(double scale)
{
    double size=scale/50;
    QGraphicsPixmapItem::setScale(size);
}

void PEnemyView::setPos(int newX, int newY)
{
    QGraphicsPixmapItem::setPos(newX*SCALE, newY*SCALE);
}

void PEnemyView::dead_slot()
{
    this->hide();
}
