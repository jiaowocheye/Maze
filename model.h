#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "maptileview.h"
#include "world.h"
#include "enemyview.h"
#include "healthpack.h"
#include "maptile.h"

class Model: public QObject
{
    Q_OBJECT
public:
    Model(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthPacks);

    std::shared_ptr<World> myWorld;
    std::vector<std::unique_ptr<Tile>> worldTiles;
    std::vector<std::unique_ptr<Tile>> worldHealthPacks;
    std::shared_ptr<World> pathFindingWorld;

    std::unique_ptr<Protagonist> protagonist;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<PEnemy>> penemies;
    std::vector<std::unique_ptr<HealthPack>> healthpacks;
    std::vector<std::unique_ptr<MapTile>> maptiles;
    std::vector<std::unique_ptr<MapTile>> rivertiles;
    unsigned int nrEnemies;
    unsigned int nrHealthPacks;

    int getNrOfEnemies();
    int getNrOfHealthPacks();

    void initialModel(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthPacks);
    //std::vector<std::unique_ptr<MapTile>> poisontiles;

private:
    //std::unique_ptr<World> myWorld;
    std::vector<std::unique_ptr<Tile>> worldmap;
};

#endif // MODEL_H
