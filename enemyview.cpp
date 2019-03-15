#include "enemyview.h"

extern int SCALE;

EnemyView::EnemyView()
{
    setPixmap(QPixmap(":/image/enemy.png"));
    EnemyView::scaleItem(SCALE);
}

void EnemyView::scaleItem(double scale)
{
    double size=scale/50;
    QGraphicsPixmapItem::setScale(size);
}

void EnemyView::setPos(int newX, int newY)
{
    QGraphicsPixmapItem::setPos(newX*SCALE, newY*SCALE);
}

void EnemyView::dead_slot()
{
    this->hide();
}
