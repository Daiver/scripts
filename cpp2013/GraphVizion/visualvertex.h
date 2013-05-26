#ifndef VISUALVERTEX_H
#define VISUALVERTEX_H

#include "typedefs.h"
#include <utility>
#include <QString>

class VisualVertex
{
public:
    VisualVertex();
    VisualVertex(graphvizion_td::Position pos);
    VisualVertex(graphvizion_td::Position pos, QString label);
    const graphvizion_td::Position& getPos();
    void setPos(graphvizion_td::Position pos);
    void setLabel(QString text);
    const QString& getLabel();
    int getSize();
protected:
    QString label;
    graphvizion_td::Position pos;
    int size;
};

#endif // VISUALVERTEX_H
