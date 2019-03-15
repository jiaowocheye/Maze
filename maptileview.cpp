#include "maptileview.h"

extern int SCALE;

MapTileView::MapTileView(float value)
{

    if(value > 0.4 && value <= 0.8)
    {
        setPixmap(QPixmap(":/image/river.png"));
        type=2;
    }
    else if(value > 0.8 && value <= 1)
    {
        setPixmap(QPixmap(":/image/grass.png"));
        type=1;
    }
    else
    {
        setPixmap(QPixmap(":/image/wall.png"));
        type=3;
    }

    scaleItem(SCALE);
}

void MapTileView::scaleItem(double scale)
{
    double size=scale/50;
    QGraphicsPixmapItem::setScale(size);
}

void MapTileView::setPos(int newX, int newY)
{
    QGraphicsPixmapItem::setPos(newX*SCALE, newY*SCALE);
}

int MapTileView::getType()
{
    return type;
}

void MapTileView::poisoned()
{
    setPixmap(QPixmap(":/image/poison.png"));
    scaleItem(SCALE);
    QTimer::singleShot(1000, this, SLOT(setBack()));
}

void MapTileView::setBack()
{
    if(getType()==2)
    {
        setPixmap(QPixmap(":/image/river.png"));
    }else
    {
        setPixmap(QPixmap(":/image/grass.png"));
    }
    scaleItem(SCALE);
}
