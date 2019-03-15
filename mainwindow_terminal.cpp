#include "mainwindow_terminal.h"
#include "ui_mainwindow_terminal.h"
#include <memory>
#include <cmath>
#include "model.h"
#include "controller.h"
#include <iostream>

using namespace std;

extern unique_ptr<Model> model;
extern unique_ptr<Controller> controller;
extern int COLUMNS, ROWS;

MainWindow_terminal::MainWindow_terminal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_terminal)
{
    ui->setupUi(this);
    init();

    connect(controller.get(),SIGNAL(meetEnemyTerminal()),this,SLOT(met_enemy()));
    connect(controller.get(),SIGNAL(meetHealthPackTerminal()),this,SLOT(met_healthpack()));

}

MainWindow_terminal::~MainWindow_terminal()
{
    delete ui;
}

void MainWindow_terminal::init()
{

    QPalette palette = ui->textBrowser->palette();
    palette.setColor(ui->textBrowser->backgroundRole(), Qt::yellow);
    ui->textBrowser->setPalette(palette);
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(dealCommand()));
    ui->textBrowser->append("You can enter \"help\" to show all commands");
}

void MainWindow_terminal::dealCommand() {
    QString s = ui->lineEdit->text();
    ui->lineEdit->clear();
    ui->textBrowser->append(">"+s);
    if (s == "go up") {
        goup();
    }
    else if (s == "go down") {
        godown();
    }
    else if (s == "go left") {
        goleft();
    }
    else if (s == "go right") {
        goright();
    }
    else if (s == "show prota") {
        showp();
    }
    else if (s=="select enemy") {
        select();
    }
    else if (s == "help") {
        help();
    }
    else {
        ui->textBrowser->append("wrong command");
    }
}

void MainWindow_terminal::goup() {
    int x, y;
    x = model->protagonist->getXPos();
    y = model->protagonist->getYPos();
    if (y == 0) {
        return;
    }
    controller->moveProtagonist(x,y-1);
}


void MainWindow_terminal::godown() {
    int x, y;
    x = model->protagonist->getXPos();
    y = model->protagonist->getYPos();
    if (y == ROWS-1) {
        return;
    }
    controller->moveProtagonist(x,y+1);
}

void MainWindow_terminal::goleft() {
    int x, y;
    x = model->protagonist->getXPos();
    y = model->protagonist->getYPos();
    if (x == 0) {
        return;
    }
    controller->moveProtagonist(x-1,y);
}

void MainWindow_terminal::goright() {
    int x, y;
    x = model->protagonist->getXPos();
    y = model->protagonist->getYPos();
    if (x == COLUMNS-1) {
        return;
    }
    controller->moveProtagonist(x+1,y);
}

void MainWindow_terminal::showp() {
    ui->textBrowser->append("protagonist at position ("+ QString::number(model->protagonist->getXPos()) + "," + QString::number(model->protagonist->getYPos()) + "),health value = " + QString::number(model->protagonist->getHealth()) + ",energy = " + QString::number(model->protagonist->getEnergy()));
}


void MainWindow_terminal::select() {
    int pi = model->protagonist->getXPos(); 
    int pj = model->protagonist->getYPos();
    double mind = sqrt(COLUMNS*COLUMNS+ROWS*ROWS)+1;
    cout<<mind<<endl;
    int mi = -1;
    for (size_t i = 0; i < model->enemies.size(); i++) {
        int ex, ey;
        ex = model->enemies.at(i)->getXPos();
        ey = model->enemies.at(i)->getYPos();
        if (sqrt((ex - pi)*(ex - pi) + (ey - pj)*(ey - pj))<mind) {
            mind = sqrt((ex - pi)*(ex - pi) + (ey - pj)*(ey - pj));
            mi = i;
        }
    }
    if (mi == -1) {
        ui->textBrowser->append("No enemy");
    }
    else {
        ui->textBrowser->append("nearest enemy found at position (" + QString::number(model->enemies.at(mi)->getXPos()) + "," +QString::number( model->enemies.at(mi)->getYPos()) + "),strength = " +QString::number( model->enemies.at(mi)->getValue()));
    }

}


void MainWindow_terminal::help() {
    ui->textBrowser->append("go up\tprotagonist go up");
    ui->textBrowser->append("go down\tprotagonist go down");
    ui->textBrowser->append( "go left\tprotagonist go left");
    ui->textBrowser->append("go right\tprotagonist go right" );
    ui->textBrowser->append( "show prota\tshow prota infomation");
    ui->textBrowser->append( "select enemy\tshow nearest enemy infomation");
}


void MainWindow_terminal::met_enemy() {
    ui->textBrowser->append("Met enemy");
}

void MainWindow_terminal::met_healthpack(){
    ui->textBrowser->append("Met healthpack");
}
