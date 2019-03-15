#ifndef NODE_H
#define NODE_H

#include "world.h"


class Node:public Tile
{
private:
    int gcost;
    int index;
    bool closed;
    int costRatio;
public:
    Node(const int  index, const int  myX, const int  myY,
         const int gcost, const bool closed, const float grayValue, const int costRatio);
    int getCost() const;
    bool getClosed() const;
    void setClosed(bool value);
    int getGcost() const;
    void setGcost(int value);
    int getIndex() const;
    void setIndex(int value);
};

#endif // NODE_H
