#include "protagonistview.h"

extern int SCALE;
extern std::unique_ptr<Model> model;

ProtagonistView::ProtagonistView()
{
    setPixmap(QPixmap(":/image/protagonist.png"));
    scaleItem(SCALE);
}

void ProtagonistView::print()
{
    std::cout<<"from protagonist, say hi"<<std::endl;
}

void ProtagonistView::scaleItem(double scale)
{
    double size=scale/50;
    QGraphicsPixmapItem::setScale(size);
}

void ProtagonistView::setPos(int newX, int newY)
{
    QGraphicsPixmapItem::setPos(newX*SCALE, newY*SCALE);
}
