#ifndef HEALTHPACKVIEW_H
#define HEALTHPACKVIEW_H

#include <QGraphicsPixmapItem>
#include "world.h"
#include "model.h"

class HealthPackView: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    HealthPackView();
    void scaleItem(double scale);
    void setPos(int x, int y);

public slots:
    void used_slot();
};

#endif // HEALTHPACKVIEW_H
