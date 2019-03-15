#include "strategy.h"
#include "pathfinding.h"
#include "controller.h"
#include <iostream>
#include <QTimer>

using namespace std;
extern unique_ptr<Model> model;
extern unique_ptr<Controller> controller;

Strategy::Strategy(const int mvision, const int mcurrent_x, const int mcurrent_y):
    vision{mvision}, current_x{mcurrent_x}, current_y{mcurrent_y}
{
    PathFinding::Destroy();
    PathFinding::Create(COLUMNS,ROWS,0);
    connect(this,SIGNAL(go_signal()),this,SLOT(go()));
    connect(this,SIGNAL(gameover()),controller.get(),SLOT(gameoverdialog()));
    connect(this,SIGNAL(congrats()),controller.get(),SLOT(congratsdialog()));
    connect(this,SIGNAL(cannot_find_enemy()),controller.get(),SLOT(noenemydialog()));
    interval = 300;
}

void Strategy::go(){
    vector<int> trace_parent(COLUMNS*ROWS,-1);
    auto pathfinding = PathFinding::Instance();

    current_x = model->protagonist->getXPos();
    current_y = model->protagonist->getYPos();


    if(model->enemies.empty()){
        cout<<"No enemies"<<endl;
        emit congrats();
        return;
    }

    cout<<model->enemies.size()<<endl;

    int nearestEnemy = -1;
    int mindis = INF, dist;
    for(int i = 0; i<model->enemies.size(); i++){
        dist = pathfinding->dis(model->enemies[i]->getXPos(),model->enemies[i]->getYPos(),current_x,current_y);
        if(dist<=vision && dist<mindis){
            nearestEnemy = i;
            mindis = dist;
        }
    }

    if(nearestEnemy == -1){
        cout<<"Cannot find an enemy"<<endl;
        emit cannot_find_enemy();
        PathFinding::Destroy();
        return;
    }

    if(model->protagonist->getHealth()<=model->enemies[nearestEnemy]->getValue()){
        int nearestPack = -1;
        int minPackDis = INF, packDist;

        for(int i = 0; i<model->healthpacks.size(); i++){
            packDist = pathfinding->dis(model->healthpacks[i]->getXPos(),model->healthpacks[i]->getYPos(),current_x,current_y);
            if(packDist<=vision && model->protagonist->getHealth()+model->healthpacks[i]->getValue()>model->enemies[nearestEnemy]->getValue() && packDist<minPackDis){
                nearestPack = i;
                minPackDis = packDist;
            }
        }

        if(nearestPack == -1){
            cout<<"Cannot find a suitable health pack"<<endl;
            emit gameover();
            PathFinding::Destroy();
            return;
        }

        endX = model->healthpacks[nearestPack]->getXPos();
        endY = model->healthpacks[nearestPack]->getYPos();
        pathfinding->findPath(endX, endY, current_x, current_y, trace_parent);
    } else {
        endX = model->enemies[nearestEnemy]->getXPos();
        endY = model->enemies[nearestEnemy]->getYPos();
        pathfinding->findPath(endX, endY, current_x, current_y, trace_parent);
    }


    trace_next.clear();
    trace_next.reserve(COLUMNS*ROWS);
    for(int i = 0; i < COLUMNS*ROWS; i++){
        trace_next[i] = -1;
    }

    px = endX, py = endY;
    cout<<current_x<<"   "<<current_y<<"   "<<endX<<"   "<<endY<<endl;
    int tx, ty;
    while(!(px==current_x && py==current_y)){
        if(px < 0 || py < 0){
            cout<<"Cannot find a valid path"<<endl;
            return;
        }
        tx = px;
        ty = py;
        px = trace_parent[tx+ty*COLUMNS]%COLUMNS;
        py = trace_parent[tx+ty*COLUMNS]/COLUMNS;
        trace_next[px+py*COLUMNS] = tx+ty*COLUMNS;
    }
    trace_next[px+py*COLUMNS] = tx+ty*COLUMNS;
    cout<<"start walking"<<endl;
    QTimer::singleShot(interval,this,SLOT(updateProtagonist()));
}

void Strategy::updateProtagonist(){
    if(model->protagonist->getEnergy()<=0 || model->protagonist->getHealth()<=0){
        emit gameover();
        return;
    }
    if(!(px==endX && py==endY)){
        controller->moveProtagonist(px,py);
        int tx,ty;
        tx = px;
        ty = py;
        px = trace_next[tx+ty*COLUMNS]%COLUMNS;
        py = trace_next[tx+ty*COLUMNS]/COLUMNS;
        QTimer::singleShot(interval,this,SLOT(updateProtagonist()));
    } else {
        controller->moveProtagonist(px,py);
        if(!model->enemies.empty()){
            emit go_signal();
        } else {
            emit congrats();
        }
    }
}

Strategy::~Strategy(){
    PathFinding::Destroy();
}
