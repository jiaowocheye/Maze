#include "model.h"
#include <iostream>
#include <QDebug>

extern int ROWS,COLUMNS,SCALE;

Model::Model(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthPacks)
{
    initialModel(filename, nrOfEnemies, nrOfHealthPacks);
}

void Model::initialModel(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthPacks)
{
    myWorld = std::make_shared<World>();
    pathFindingWorld=std::make_shared<World>();
    worldTiles = myWorld->createWorld(QString(filename));
    protagonist=myWorld->getProtagonist();
    enemies = myWorld->getEnemies(nrOfEnemies);
    worldHealthPacks=myWorld->getHealthPacks(nrOfHealthPacks);
    ROWS = myWorld->getRows();
    COLUMNS = myWorld->getCols();

    nrEnemies=nrOfEnemies;
    nrHealthPacks=nrOfHealthPacks;

    maptiles.reserve(ROWS*COLUMNS);
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            auto & tile = worldTiles.at(i*COLUMNS+j);
            int x = tile->getXPos();
            int y = tile->getYPos();
            float value = tile->getValue();

            auto maptile = std::make_unique<MapTile>(x,y,value);
            maptiles.push_back(std::move(maptile));

            if(value > 0.4 && value <= 0.8)
                rivertiles.push_back(std::move(maptile));
        }
    }

    healthpacks.reserve(nrOfHealthPacks);
    for(auto &healthpack: worldHealthPacks)
    {
        auto thehealthpack=std::make_unique<HealthPack>(healthpack->getXPos(),healthpack->getYPos(),healthpack->getValue());
        healthpacks.push_back(std::move(thehealthpack));
    }
}

int Model::getNrOfEnemies()
{
    return nrEnemies;
}

int Model::getNrOfHealthPacks()
{
    return nrHealthPacks;
}
