#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protagonistview.h"
#include "model.h"
#include "maptileview.h"
#include "controller.h"
#include <iostream>
#include <QDebug>
#include <memory>
#include "pathfinding.h"
#include "strategy.h"

extern std::unique_ptr<Controller> controller;
extern std::unique_ptr<Model> model;
extern int SCALE;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadMap();
    gameSetting();

    initialGame();

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(resetGame()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(pathFinding()));
    connect(ui->pushButtonS, SIGNAL(clicked()), this, SLOT(smallScale()));
    connect(ui->pushButtonM, SIGNAL(clicked()), this, SLOT(middleScale()));
    connect(ui->pushButtonL, SIGNAL(clicked()), this, SLOT(largeScale()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D)
        emit protagonistGo(RIGHT);
    else if(event->key() == Qt::Key_A)
        emit protagonistGo(LEFT);
    else if(event->key() == Qt::Key_S)
        emit protagonistGo(DOWN);
    else if(event->key() == Qt::Key_W)
        emit protagonistGo(UP);
}

void MainWindow::gameoverdialog()
{
    GameOverDialog *gameoverdialog=new GameOverDialog();
    gameoverdialog->show();
}

void MainWindow::congratsdialog()
{
    CongratsDialog *congratsdialog=new CongratsDialog();
    congratsdialog->show();
}

void MainWindow::initialGame()
{
    modeflag=0;

    scene=new MyScene();

    controller=std::make_unique<Controller>();

    SCALE=15;

    model=std::make_unique<Model>(file, nrOfEnemies, nrOfPacks);

    model->protagonist->setPos(4,0);

    scene->addAll();
    ui->graphicsView->setScene(scene);
    Strategy *strategy =new Strategy(vision, model->protagonist->getXPos(), model->protagonist->getYPos());
    connect(ui->pushButton, SIGNAL(clicked()), strategy, SLOT(go()));
    ui->Health->setValue(model->protagonist->getHealth());//TODO: replace 100 with protag->getValue
    ui->Energy->setValue(model->protagonist->getEnergy());
    ui->graphicsView->resize(490,490);

    //update UI health
    connect(model->protagonist.get(),SIGNAL(healthChanged(int)),ui->Health,SLOT(setValue(int)));
    connect(model->protagonist.get(),SIGNAL(energyChanged(int)),ui->Energy,SLOT(setValue(int)));

    connect(this,SIGNAL(protagonistGo(DIRECTION)),(controller.get()),SLOT(moveProtagonist(DIRECTION)));
    connect(model->protagonist.get(),SIGNAL(posChanged(int,int)), scene,SLOT(moveProtagonistViewSlot(int,int)));
    connect(controller.get(),SIGNAL(poisonLeakedSignal(int, int)),scene,SLOT(poisonLeakedSlot(int,int)));

    connect(controller.get(), SIGNAL(gameover()), controller.get(), SLOT(gameoverdialog()));
    connect(controller.get(), SIGNAL(congrats()), controller.get(), SLOT(congratsdialog()));
}

void MainWindow::resetGame()
{
    scene->clear();
    initialGame();
}

void MainWindow::loadMap()
{
    //select world map
    file=QFileDialog::getOpenFileName(this, tr("Choose World"),"/home","Image File (*.png)");

    if(file.isEmpty())
    {
        file=":/image/maze2.png"; //default
    }
}

void MainWindow::gameSetting()
{
    QDialog dialog(this);
    QFormLayout formLayout(&dialog);

    QLineEdit * enemyLineEdit = new QLineEdit(&dialog);
    QLineEdit * packLineEdit = new QLineEdit(&dialog);
    QLineEdit * visionEdit =new QLineEdit(&dialog);

    //set limit to integer number
    enemyLineEdit->setValidator(new QIntValidator(0,100,this));
    packLineEdit->setValidator(new QIntValidator(0,100,this));
    visionEdit->setValidator(new QIntValidator(0,100,this));

    formLayout.addRow(new QLabel("Choose the number of enemies and health packs"));
    formLayout.addRow(tr("#Enemies:"),enemyLineEdit);
    formLayout.addRow(tr("#HealthPacks:"),packLineEdit);
    formLayout.addRow(tr("#Vision Set: (>=1000)"),visionEdit);

    //add check button--ok and cancel
    QDialogButtonBox buttonBox (QDialogButtonBox::Ok| QDialogButtonBox::Cancel);
    connect(&buttonBox, SIGNAL(accepted()),&dialog,SLOT(accept()));
    connect(&buttonBox, SIGNAL(rejected()),&dialog,SLOT(reject()));

    formLayout.addRow(&buttonBox);

    //show dialog
    int result = dialog.exec();//exec return value is int

    //check if the button is checked
    if(result == QDialog::Accepted)
    {
        if(!enemyLineEdit->text().isEmpty() && enemyLineEdit->text()!="0")
            nrOfEnemies=enemyLineEdit->text().toUInt();
        if(!packLineEdit->text().isEmpty())
            nrOfPacks=packLineEdit->text().toUInt();
        if(!visionEdit->text().isEmpty())
            vision=visionEdit->text().toInt();
    }
    else
    {//button canceled
        QMessageBox::information(this, tr("User setting"),
                                 tr("Using default setting"));
        return;
    }
}

void MainWindow::pathFinding()
{

    QDialog dialog(this);
    QFormLayout formLayout(&dialog);

    QLineEdit * startXLineEdit = new QLineEdit(&dialog);
    QLineEdit * endXLineEdit = new QLineEdit(&dialog);
    QLineEdit * startYLineEdit = new QLineEdit(&dialog);
    QLineEdit * endYLineEdit = new QLineEdit(&dialog);

    //set limit to integer number
    startXLineEdit->setValidator(new QIntValidator(0,2400,this));
    endXLineEdit->setValidator(new QIntValidator(0,2380,this));
    startYLineEdit->setValidator(new QIntValidator(0,2400,this));
    endYLineEdit->setValidator(new QIntValidator(0,2380,this));

    formLayout.addRow(new QLabel("Choose the start and end point of pathfinding"));
    formLayout.addRow(tr("START X:"),startXLineEdit);
    formLayout.addRow(tr("START Y:"),startYLineEdit);
    formLayout.addRow(tr("END X:"),endXLineEdit);
    formLayout.addRow(tr("END Y"),endYLineEdit);

    //add check button--ok and cancel
    QDialogButtonBox buttonBox (QDialogButtonBox::Ok| QDialogButtonBox::Cancel);
    connect(&buttonBox, SIGNAL(accepted()),&dialog,SLOT(accept()));
    connect(&buttonBox, SIGNAL(rejected()),&dialog,SLOT(reject()));

    formLayout.addRow(&buttonBox);

    //show dialog
    int result = dialog.exec();//exec return value is int

    //check if the button is checked
    if(result == QDialog::Accepted)
    {
        if(!startXLineEdit->text().isEmpty())
            startX=startXLineEdit->text().toInt();
        if(!startXLineEdit->text().isEmpty())
            startY=startYLineEdit->text().toInt();
        if(!endXLineEdit->text().isEmpty())
            endX=endXLineEdit->text().toInt();
        if(!endYLineEdit->text().isEmpty())
            endY=endYLineEdit->text().toInt();
    }
    else
    {//button canceled
        QMessageBox::information(this, tr("User setting"),
                                 tr("Using default setting"));
        return;
    }

    scene->clear();
    modeflag=1;
    maze3=QPixmap(":/image/maze3.png");

    model->worldTiles = model->pathFindingWorld->createWorld(":/image/maze3.png");
    const int width = model->pathFindingWorld->getCols();
    const int height = model->pathFindingWorld->getRows();

    /*maze3*/

    vector<int> parent(width*height,-1);

    PathFinding::Destroy();
    PathFinding::Create(width,height,1);

    clock_t t1 = clock();
    PathFinding::Instance()->findPath(endX,endY,startX,startY,parent);
    clock_t t2 = clock();
    double dt = (double)(t2-t1)/CLOCKS_PER_SEC;

    cout<<dt<<endl;


    /*show the path on the map*/
    QPainter painter(&maze3);
    QBrush brush(Qt::red);
    QPen pen(brush,3);
    painter.setBrush(brush);
    painter.setPen(pen);

    int px = endX, py = endY;

    while(!(px==startX && py==startY)){
        if(px < 0 || py < 0){
            cout<<"Cannot find a valid path"<<endl;
            return;
        }
        int tx = px;
        int ty = py;
        px = parent[tx+ty*width]%width;
        py = parent[tx+ty*width]/width;
        painter.drawLine(px,py,tx,ty);
    }

    scene->addPixmap(maze3);


    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(1000,1000);
}

void MainWindow::smallScale()
{
    scene->clear();
    if(modeflag==0)
    {
        SCALE=10;
        scene->addAll();
    }else
    {
        scene->addPixmap(maze3.scaled(480,480));
    }
}

void MainWindow::middleScale()
{
    scene->clear();
    if(modeflag==0)
    {
        SCALE=15;
        scene->addAll();
    }else
    {
        scene->addPixmap(maze3.scaled(800,800));
    }
}

void MainWindow::largeScale()
{
    scene->clear();
    if(modeflag==0)
    {
        SCALE=30;
        scene->addAll();
    }else
    {
        scene->addPixmap(maze3);
    }
}
