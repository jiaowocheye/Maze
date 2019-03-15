#include "maptile.h"

MapTile::MapTile(int x, int y, float value):Tile(x,y,value),poison{0.0f}
{

}

void MapTile::setVPoisonValue(float newValue)
{
    poison = newValue;
    //emit poiValueChanged();
}

float MapTile::getPoison() const
{
    return poison;
}

void MapTile::setPoison(float value)
{
    poison = value;
}
