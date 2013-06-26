#include "visualvertexmarktool.h"

VisualVertexMarkTool::VisualVertexMarkTool()
{
}

void VisualVertexMarkTool::mouseReleaseEvent(QMouseEvent *e, VisualGraph *g)
{
}

void VisualVertexMarkTool::mouseMoveEvent(QMouseEvent *e, VisualGraph *g)
{
}

void VisualVertexMarkTool::mousePressEvent(QMouseEvent *e, VisualGraph *g)
{
    g->markVertex(g->getVertexIndexByCoo(graphvizion_td::Position(e->x(), e->y())));
}

void VisualVertexMarkTool::paintEvent(QPaintEvent *e, QPainter *painter, VisualGraph *g)
{
}
