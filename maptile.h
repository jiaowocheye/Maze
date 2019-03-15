#ifndef MAPTILE_H
#define MAPTILE_H

#include "world.h"
#include <QObject>

class MapTile: public QObject, public Tile
{
    Q_OBJECT
public:
    MapTile(int x, int y, float value);
    virtual ~MapTile() = default;
    void setVPoisonValue(float newValue);
    float getPoison() const;
    void setPoison(float value);

signals:
    //void poiValueChanged();

private:
    float poison;
};

#endif // MAPTILE_H
