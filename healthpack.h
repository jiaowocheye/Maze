#ifndef HEALTHPACK_H
#define HEALTHPACK_H

#include "world.h"
#include <QObject>

class HealthPack: public QObject, public Tile
{
    Q_OBJECT
public:
    HealthPack(int xPosition, int yPosition, float value);
    virtual ~HealthPack() = default;
    void setUsed(bool b);

signals:
    void used_signal();

private:
    bool used;
};

#endif // HEALTHPACK_H
