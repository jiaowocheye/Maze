#ifndef MYPROTAGONIST_H
#define MYPROTAGONIST_H

#include <QGraphicsPixmapItem>
#include <QSize>
#include <iostream>
#include "world.h"
#include "model.h"

class ProtagonistView: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ProtagonistView();
    void print();
    void scaleItem(double scale);
    void setPos(int x, int y);

public slots:
    //void moveProtagonistViewSlot(int x, int y);

};

#endif // MYPROTAGONIST_H
