#ifndef MYTILE_H
#define MYTILE_H

#include "world.h"
//#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class MapTileView: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MapTileView(float value);
    void scaleItem(double scale);
    void setPos(int x, int y);
    void poisoned();
    int type;
    int getType();

public slots:
    void setBack();

private:
    float poison;
};

#endif // MYTILE_H
