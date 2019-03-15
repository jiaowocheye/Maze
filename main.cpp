#include "mainwindow.h"
#include "mainwindow_terminal.h"
#include <QApplication>

int ROWS, COLUMNS, SCALE;
std::unique_ptr<Controller> controller;
std::unique_ptr<Model> model;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MainWindow_terminal wt;

    wt.show();
    w.show();

    return a.exec();
}
