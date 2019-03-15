#ifndef MYENEMY_H
#define MYENEMY_H

#include "world.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class EnemyView: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    EnemyView();
    void scaleItem(double scale);
    void setPos(int x, int y);

public slots:
    void dead_slot();
};

#endif // MYENEMY_H
