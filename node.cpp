#include "node.h"

int Node::getGcost() const
{
    return gcost;
}

void Node::setGcost(int value)
{
    gcost = value;
}

int Node::getIndex() const
{
    return index;
}

void Node::setIndex(int value)
{
    index = value;
}

Node::Node(const int  myIndex, const int  myX, const int  myY, const int myGcost,
           const bool myClosed, const float myGrayValue, const int mcostRatio):
    Tile(myX,myY,myGrayValue), gcost{myGcost}, index{myIndex}, closed{myClosed}, costRatio{mcostRatio}
{

}

int Node::getCost() const
{
    return costRatio*gcost;
}

bool Node::getClosed() const
{
    return closed;
}

void Node::setClosed(bool value)
{
    closed = value;
}
