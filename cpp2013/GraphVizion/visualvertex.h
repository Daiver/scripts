#ifndef VISUALVERTEX_H
#define VISUALVERTEX_H

#include "typedefs.h"
#include <utility>
#include <string>

class VisualVertex
{
public:
    VisualVertex();
    VisualVertex(graphvizion_td::Position pos);
    VisualVertex(graphvizion_td::Position pos, std::string label);
    const graphvizion_td::Position& getPos();
    void setPos(graphvizion_td::Position pos);
    const std::string& getLabel();
    int getSize();
protected:
    std::string label;
    graphvizion_td::Position pos;
    int size;
};

#endif // VISUALVERTEX_H
