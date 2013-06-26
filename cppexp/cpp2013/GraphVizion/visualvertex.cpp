#include "visualvertex.h"

VisualVertex::VisualVertex()
{
    this->size = 10;
}

VisualVertex::VisualVertex(graphvizion_td::Position pos):VisualVertex()
{
    this->pos = pos;
}

VisualVertex::VisualVertex(graphvizion_td::Position pos, QString label):VisualVertex(pos)
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
}

void VisualVertex::setLabel(QString text)
{
    this->label = text;
}

const QString &VisualVertex::getLabel()
{
    return this->label;
}

int VisualVertex::getSize()
{
    return this->size;
}
