#include "visualvertex.h"

VisualVertex::VisualVertex()
{
}

VisualVertex::VisualVertex(graphvizion_td::Position pos)
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

const std::string &VisualVertex::getLabel()
{
    return this->label;
}
