#include "visualvertex.h"
#include <iostream>

VisualVertex::VisualVertex()
{
    this->size = 10;
}

VisualVertex::VisualVertex(graphvizion_td::Position pos):VisualVertex()
{
    this->pos = pos;
}

VisualVertex::VisualVertex(graphvizion_td::Position pos, std::string label):VisualVertex(pos)
{
    this->label = label;
}

const graphvizion_td::Position &VisualVertex::getPos()
{
    return this->pos;
}

void VisualVertex::setPos(graphvizion_td::Position pos)
{
    this->pos = pos;
    //std::cout<<this->pos.first<<" "<<this->pos.second<<pos.first<<" "<<pos.second<<"\n";
}

const std::string &VisualVertex::getLabel()
{
    return this->label;
}

int VisualVertex::getSize()
{
    return this->size;
}
