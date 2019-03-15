#include "myscene.h"
#include <iostream>

extern int SCALE, ROWS, COLUMNS;
extern std::unique_ptr<Model> model;
extern std::unique_ptr<Controller> controller;

MyScene::MyScene()
{

}

void MyScene::addProtagonist()
{
    protagonistview=new ProtagonistView();
    QGraphicsScene::addItem(protagonistview);
    int xpos=model->protagonist->getXPos();
    int ypos=model->protagonist->getYPos();
    protagonistview->setPos(xpos,ypos);
}

void MyScene::addMap()
{
    for(auto &maptile: model->maptiles)
    {
        int xpos=maptile->getXPos();
        int ypos=maptile->getYPos();
        float value=maptile->getValue();
        MapTileView *mapview=new MapTileView(value);
        mapview->setPos(xpos, ypos);
        maptileviews.push_back(mapview);
        addItem(mapview);
    }
}

void MyScene::addEnemy()
{
    for(auto & enemy: model->enemies)
    {
        if(dynamic_cast<PEnemy *>(enemy.get()))
        {
            PEnemyView *penemyview=new PEnemyView();
            connect(enemy.get(), SIGNAL(dead()), penemyview, SLOT(dead_slot()));
            int xpos=enemy->getXPos();
            int ypos=enemy->getYPos();
            penemyview->setPos(xpos,ypos);
            penemyviews.push_back(penemyview);
            addItem(penemyview);
        }
        else
        {
            EnemyView *enemyview=new EnemyView();
            connect(enemy.get(), SIGNAL(dead()), enemyview, SLOT(dead_slot()));
            int xpos=enemy->getXPos();
            int ypos=enemy->getYPos();
            enemyview->setPos(xpos,ypos);
            enemyviews.push_back(enemyview);
            addItem(enemyview);
        }
    }
}

void MyScene::addHealthPack()
{
    for(auto & healthpack: model->healthpacks)
    {
        HealthPackView *healthpackview=new HealthPackView();
        connect(healthpack.get(), SIGNAL(used_signal()), healthpackview, SLOT(used_slot()));
        int xpos=healthpack->getXPos();
        int ypos=healthpack->getYPos();
        healthpackview->setPos(xpos,ypos);
        healthpackviews.push_back(healthpackview);
        addItem(healthpackview);
    }
}

void MyScene::addAll()
{
    addMap();
    addProtagonist();
    addEnemy();
    addHealthPack();
}

void MyScene::moveProtagonistViewSlot(int x, int y)
{
    protagonistview->setPos(x, y);
}

void MyScene::poisonLeakedSlot(int x, int y)
{
    maptileviews.at(x+y*COLUMNS)->poisoned();

    int type;

    //x-1,y-1
    if(maptileviews.at((x-1)+(y-1)*COLUMNS)->getType()!=3)
        maptileviews.at((x-1)+(y-1)*COLUMNS)->poisoned();
    //x,y-1
    if(maptileviews.at(x+(y-1)*COLUMNS)->getType()!=3)
        maptileviews.at(x+(y-1)*COLUMNS)->poisoned();
    //x+1,y-1
    if(maptileviews.at((x+1)+(y-1)*COLUMNS)->getType()!=3)
        maptileviews.at((x+1)+(y-1)*COLUMNS)->poisoned();
    //x-1,y
    if(maptileviews.at((x-1)+y*COLUMNS)->getType()!=3)
        maptileviews.at((x-1)+y*COLUMNS)->poisoned();
    //x+1,y
    if(maptileviews.at((x+1)+y*COLUMNS)->getType()!=3)
        maptileviews.at((x+1)+y*COLUMNS)->poisoned();
    //x-1,y+1
    if(maptileviews.at((x-1)+(y+1)*COLUMNS)->getType()!=3)
        maptileviews.at((x-1)+(y+1)*COLUMNS)->poisoned();
    //x,y+1
    if(maptileviews.at(x+(y+1)*COLUMNS)->getType()!=3)
        maptileviews.at(x+(y+1)*COLUMNS)->poisoned();
    //x+1,y+1
    if(maptileviews.at((x+1)+(y+1)*COLUMNS)->getType()!=3)
        maptileviews.at((x+1)+(y+1)*COLUMNS)->poisoned();
}
