#ifndef PENEMYVIEW_H
#define PENEMYVIEW_H

#include "world.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class PEnemyView: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PEnemyView();
    void scaleItem(double scale);
    void setPos(int x, int y);

public slots:
    void dead_slot();
};

#endif // PENEMYVIEW_H
