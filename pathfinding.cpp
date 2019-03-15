#include "pathfinding.h"
#include <queue>
#include <iostream>
#include "model.h"

PathFinding* PathFinding::instance = nullptr;

extern unique_ptr<Model> model;

PathFinding::PathFinding(const int  myWidth, const int  myHeight, const int myRatio):
    width{myWidth}, height{myHeight}, costRatio{myRatio}
{
    for(int i = 0; i< model->worldTiles.size(); i++){
        nodes.push_back(new Node(i,model->worldTiles[i]->getXPos(),model->worldTiles[i]->getYPos(),-1,false,model->worldTiles[i]->getValue(), costRatio));
    }
}

void PathFinding::findPath(int endX, int endY, int startX, int startY, vector<int>& parent)
{
    if(startY == endY && startX == endX) return;
    int endIndex = endX+endY*width;

    /*initialize nodes*/
    for(auto node:nodes){
        node->setGcost(dis(node->getXPos(),node->getYPos(),endX,endY));
        node->setClosed(false);
    }

    for(auto p:parent){
        p = -1;
    }

    int tx, ty, tfcost;
    unsigned long txy;

    /*algorithm*/
    pair<Node*,int>* n;
    open.push(new pair<Node*,int>(nodes[startX+startY*width],0));

    while(!open.empty()){
        n = open.top();
        //cout<<n->getX()<<"   "<<n->getY()<<"   "<<n->getCost()<<endl;
        open.pop();
        if(n->first->getClosed()) {delete n; continue;}
        n->first->setClosed(true);
        if(n->first->getIndex() == endIndex) {
            delete n;
            break;
        }

        for(int i=0;i<4;i++){
            tx = n->first->getXPos()+dx[i];
            ty = n->first->getYPos()+dy[i];
            if(tx<0 || tx>=width || ty<0 || ty>=height || nodes[tx+ty*width]->getClosed()==true) continue;
            txy = tx+ty*width;

            if(nodes[txy]->getValue()<=1){

                if(nodes[txy]->getValue()>0.8){
                    tfcost = 1 + n->second;
                }else{
                    tfcost = 3 + n->second;
                }

                parent[txy] = n->first->getIndex();
                open.push(new pair<Node*,int>(nodes[txy],tfcost));
            }
        }

        delete n;
    }
    while(!open.empty()) {delete open.top(); open.pop();}
}
