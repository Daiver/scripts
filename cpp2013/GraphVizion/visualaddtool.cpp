#include "visualaddtool.h"

VisualAddTool::VisualAddTool()
{
}

void VisualAddTool::mouseReleaseEvent(QMouseEvent *e, VisualGraph *g)
{
}

void VisualAddTool::mouseMoveEvent(QMouseEvent *e, VisualGraph *g)
{
}

void VisualAddTool::mousePressEvent(QMouseEvent *e, VisualGraph *g)
{
    g->addVertex(VisualVertex(graphvizion_td::Position(e->x(), e->y())));
}
