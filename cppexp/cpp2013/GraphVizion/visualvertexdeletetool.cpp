#include "visualvertexdeletetool.h"
#include "visualtool.h"

#include <QDebug>

VisualVertexDeleteTool::VisualVertexDeleteTool()
{
}

void VisualVertexDeleteTool::mouseReleaseEvent(QMouseEvent *e, VisualGraph *g)
{
}

void VisualVertexDeleteTool::mouseMoveEvent(QMouseEvent *e, VisualGraph *g)
{
}

void VisualVertexDeleteTool::mousePressEvent(QMouseEvent *e, VisualGraph *g)
{
    g->deleteByIndex(g->getVertexIndexByCoo(graphvizion_td::Position(e->x(), e->y())));
}

void VisualVertexDeleteTool::paintEvent(QPaintEvent *e, QPainter *painter, VisualGraph *g)
{
}
