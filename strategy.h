#ifndef STRATEGY_H
#define STRATEGY_H

#ifndef INF
#define INF 1000000000
#endif // INF

#include <memory>
#include <vector>
#include "model.h"
#include "protagonistview.h"

extern int ROWS, COLUMNS;
extern std::unique_ptr<Model> model;

using namespace std;

class Strategy:public QObject
{
    Q_OBJECT
private:
    const int vision;
    int current_x;
    int current_y;

    int px;
    int py;
    int endX;
    int endY;
    int interval;
    std::vector<int> trace_next;

public:
    Strategy(const int vision, const int current_x, const int current_y);
    ~Strategy();

signals:
    void go_signal();
    void gameover();
    void cannot_find_enemy();
    void congrats();

public slots:
    void go();
    void updateProtagonist();
};

#endif // STRATEGY_H
