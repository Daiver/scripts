#include "visualvertexaddtool.h"

VisualVertexAddTool::VisualVertexAddTool()
{
}

void VisualVertexAddTool::mouseReleaseEvent(QMouseEvent *e, VisualGraph *g)
{
}

void VisualVertexAddTool::mouseMoveEvent(QMouseEvent *e, VisualGraph *g)
{
}

void VisualVertexAddTool::mousePressEvent(QMouseEvent *e, VisualGraph *g)
{
    g->addVertex(VisualVertex(graphvizion_td::Position(e->x(), e->y())));
}

void VisualVertexAddTool::paintEvent(QPaintEvent *e, QPainter *painter, VisualGraph *g)
{
}

