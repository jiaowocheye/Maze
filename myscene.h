#ifndef MYSCENE_H
#define MYSCENE_H

#include "protagonistview.h"
#include "healthpackview.h"
#include "penemyview.h"
#include "enemyview.h"
#include "model.h"
#include "controller.h"
#include "maptileview.h"
#include <QObject>
#include <QPixmap>
#include <QGraphicsScene>

class MyScene: public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene();
    virtual ~MyScene()=default;
    ProtagonistView *protagonistview;
    std::vector<EnemyView *> enemyviews;
    std::vector<PEnemyView *> penemyviews;
    std::vector<HealthPackView *> healthpackviews;
    std::vector<MapTileView *> maptileviews;
    void addProtagonist();
    void addMap();
    void addEnemy();
    void addHealthPack();
    void addAll();

public slots:
    void moveProtagonistViewSlot(int x, int y);
    void poisonLeakedSlot(int x, int y);
};


#endif // MYSCENE_H
