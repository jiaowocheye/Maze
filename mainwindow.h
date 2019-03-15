#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsView>
#include <QPixmap>
#include <QHBoxLayout>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QIntValidator>
#include "protagonistview.h"
#include "world.h"
#include "myscene.h"
#include "controller.h"
#include "strategy.h"
#include "gameoverdialog.h"
#include "gamesettingdialog.h"
#include "congratsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void initialGame();
    void loadMap();
    void gameSetting();

public slots:
    void gameoverdialog();
    void congratsdialog();
    void resetGame();
    void pathFinding();
    void smallScale();
    void middleScale();
    void largeScale();

signals:
    void protagonistGo(DIRECTION d);
    void testsignal(int i);

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    MyScene *scene;
    QPixmap maze3;
    QString file;
    unsigned int nrOfPacks=2;//default
    unsigned int nrOfEnemies=2;//default
    int vision=5000;
    int endX = 1170;
    int endY = 1200;
    int startX = 20;
    int startY = 20;
    int modeflag=0; //0=peppa, 1=pathfinding
};

#endif // MAINWINDOW_H
