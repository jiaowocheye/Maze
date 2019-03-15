#include "controller.h"

extern std::unique_ptr<Model> model;
extern int ROWS, COLUMNS, SCALE;
#include <QTimer>
#include "unistd.h"

Controller::Controller()
{

}

void Controller::moveProtagonist(DIRECTION d)
{
    int xpos=model->protagonist->getXPos();
    int ypos=model->protagonist->getYPos();

    if(model->protagonist->getEnergy()<=0 || model->protagonist->getHealth()<=0)
    {
        emit gameover();
    }else if(model->enemies.size()==0)
    {
        emit congrats();
    }

    if(d == UP)
    {
        if(checkTile(xpos,ypos-1)!=-2)
            model->protagonist->setPos(xpos,ypos-1);
    }
    else if(d == DOWN)
    {
        if(checkTile(xpos,ypos+1)!=-2)
            model->protagonist->setPos(xpos,ypos+1);
    }
    else if(d == LEFT)
    {
        if(checkTile(xpos-1,ypos)!=-2)
            model->protagonist->setPos(xpos-1,ypos);
    }
    else if(d == RIGHT)
    {
        if(checkTile(xpos+1,ypos)!=-2)
            model->protagonist->setPos(xpos+1,ypos);
    }

    xpos=model->protagonist->getXPos();
    ypos=model->protagonist->getYPos();
}

int Controller::checkTile(int x, int y)
{
    if(x<0 || y<0 || x>ROWS || y>COLUMNS)
    {
        return -2;
    }else
    {
        float value=model->worldTiles.at(x+y*COLUMNS)->getValue();
        if(value!=std::numeric_limits<float>::infinity())
        {
            float energy=model->protagonist->getEnergy();
            //enemy
            for(int i =0;i<model->enemies.size();i++)
            {
                if(model->enemies.at(i)->getXPos()==x && model->enemies.at(i)->getYPos()==y)
                    return meetEnemy(i);
            }

            //healthpack
            for(int i =0;i<model->healthpacks.size();i++)
            {
                if(model->healthpacks.at(i)->getXPos()==x && model->healthpacks.at(i)->getYPos()==y)
                {
                    model->protagonist->setEnergy(energy-0.3);
                    return meetHealthPack(i);
                }
            }

            //river
            if(value > 0.4 && value <= 0.8)
            {
                model->protagonist->setEnergy(energy-1);
                return 3;
            }


            //grass
            model->protagonist->setEnergy(energy-0.3);
            return 4;
        }
        return -2;
    }
}

int Controller::meetEnemy(int id)
{
    float health = model->protagonist->getHealth();
    float damage = model->enemies.at(id)->getValue();

    int xpos=model->enemies.at(id)->getXPos();
    int ypos=model->enemies.at(id)->getYPos();

    if(dynamic_cast<PEnemy *>(model->enemies.at(id).get()))
        emit poisonLeakedSignal(xpos, ypos);


    model->protagonist->setHealth(health-damage);
    model->protagonist->setEnergy(100);
    model->enemies.at(id)->setDefeated(true);
    model->enemies.erase(model->enemies.begin()+id);

    emit meetEnemyTerminal();

    return id;
}

int Controller::meetHealthPack(int id)
{
    float health = model->protagonist->getHealth();
    float added=model->healthpacks.at(id)->getValue();

    int newHealth;
    if(health+added<=100) newHealth = health+added;
    else newHealth = 100;
    model->protagonist->setHealth(newHealth);
    model->healthpacks.at(id)->setUsed(true);
    model->healthpacks.erase(model->healthpacks.begin()+id);
    std::cout<<"health added "<<added<<std::endl;

    emit meetHealthPackTerminal();

    return 2;
}


void Controller::moveProtagonist(int x, int y)
{
    if(model->protagonist->getEnergy()<=0 || model->protagonist->getHealth()<=0)
    {
        emit gameover();
        return;
    }else if(model->enemies.size()==0)
    {
        std::cout<<"emit congrats"<<std::endl;
        emit congrats();
        return;
    }

    int id=checkTile(x,y);

    if(id!=-2)
    {
        model->protagonist->setPos(x,y);

        int xpos=model->protagonist->getXPos();
        int ypos=model->protagonist->getYPos();
        std::cout<<xpos<<","<<ypos<<std::endl;
        //std::cout<<"meet enemy "<<id<<std::endl;
    }else
    {
        std::cout<<"out of range"<<std::endl;
    }
}

void Controller::gameoverdialog()
{
    GameOverDialog *gameoverdialog=new GameOverDialog();
    gameoverdialog->show();
}

void Controller::congratsdialog()
{
    CongratsDialog *congratsdialog=new CongratsDialog();
    congratsdialog->show();
}

void Controller::noenemydialog()
{
    NoEnemyDialog *noenemydialog=new NoEnemyDialog();
    noenemydialog->show();
}
