#include "visualvertexmovetool.h"
#include "visualvertex.h"
#include "visualgraph.h"
#include "math.h"

VisualVertexMoveTool::VisualVertexMoveTool()
{
    this->isPressed = false;
}

void VisualVertexMoveTool::mouseReleaseEvent(QMouseEvent *e, VisualGraph *g)
{
    this->isPressed = false;
    this->vertex = nullptr;
}

void VisualVertexMoveTool::mouseMoveEvent(QMouseEvent *e, VisualGraph *g)
{
    if(this->isPressed)
    {
        this->vertex->setPos(graphvizion_td::Position(e->x(), e->y()));
    }
}

void VisualVertexMoveTool::mousePressEvent(QMouseEvent *e, VisualGraph *g)
{
    auto vertex = g->getVertexByCoo(graphvizion_td::Position(e->x(), e->y()));
    if (vertex != nullptr)
    {
        this->isPressed = true;
        this->vertex = vertex;
    }
}

void VisualVertexMoveTool::paintEvent(QPaintEvent *e, QPainter *painter, VisualGraph *g)
{
}
