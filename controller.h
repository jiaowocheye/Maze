#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "gameoverdialog.h"
#include "congratsdialog.h"
#include "noenemydialog.h"
#include <QObject>
#include <iostream>
#include <QDebug>


enum DIRECTION{UP, DOWN, LEFT, RIGHT};

class Controller: public QObject
{
    Q_OBJECT
public:
    Controller();
    int checkTile(int x, int y);
    void createModel();
    int meetEnemy(int id);
    int meetHealthPack(int id);
    int meetGrassTile();
    int meetRiverTile();
    void moveProtagonist(int x, int y);

signals:
    void moveProtagonistView(int x,int y);
    void enemySignal(int x, int y);
    void poisonLeakedSignal(int x, int y);
    void gameover();
    void congrats();
    void meetEnemyTerminal();
    void meetHealthPackTerminal();

public slots:
    void moveProtagonist(DIRECTION d);
    void gameoverdialog();
    void congratsdialog();
    void noenemydialog();
};

#endif // CONTROLLER_H
