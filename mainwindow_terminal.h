#ifndef MAINWINDOW_TERMINAL_H
#define MAINWINDOW_TERMINAL_H

#include <QMainWindow>

namespace Ui {
class MainWindow_terminal;
}

class MainWindow_terminal : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_terminal(QWidget *parent = nullptr);
    void init();
    void goup();
    void godown();
    void goleft();
    void goright();
    void showp();
    void select();
    void help();
    ~MainWindow_terminal();

private:
    Ui::MainWindow_terminal *ui;

public slots:
    void dealCommand();
    void met_enemy();
    void met_healthpack();
};

#endif // MAINWINDOW_TERMINAL_H
