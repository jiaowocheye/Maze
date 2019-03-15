#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <cmath>
#include "node.h"
#include <vector>
#include <queue>

using namespace std;

class PathFinding
{
private:
    int width;
    int height;
    int costRatio;
    vector<Node*> nodes;


    const int dx[4] = {1, 0, -1, 0};          //right, down, left, up
    const int dy[4] = {0, 1, 0, -1};

    struct cmp{
        bool operator()(const pair<Node*,int>* a, const pair<Node*,int>* b){
            return a->first->getCost()+a->second > b->first->getCost()+b->second;
        }
    };
    priority_queue<pair<Node*,int>*, vector<pair<Node*,int>*>, cmp> open;

    PathFinding(const int width, const int  height, const int costRatio);
    static PathFinding * instance;

public:
    int dis(int x1, int y1, int x2, int y2){return abs(x1-x2)+abs(y1-y2);}
    void findPath(int endX, int endY, int startX, int startY, vector<int>& parent);
    static void Create(const int  w, const int  h, const int r){
        if(instance != nullptr)
            return;

        instance = new PathFinding(w, h, r);
    }
    static void Destroy(){
        delete instance;
        instance = nullptr;
    }
    static PathFinding* Instance(){
        return instance;
    }
    ~PathFinding(){
        for(auto node:nodes){
            delete node;
        }
    }
};

#endif // PATHFINDING_H
