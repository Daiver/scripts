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
    std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp;
    for (vp = boost::vertices(g->graph); vp.first != vp.second; ++vp.first)
    {
        VisualVertex v = g->getByIterator(vp); //getByIndex(index[*vp.first]);
        if(sqrt(pow(e->x() - v.getPos().first, 2.0 ) + pow(e->y() - v.getPos().second, 2.0)) <= v.getSize())
        {
            this->isPressed = true;
            this->vertex = &g->getByIterator(vp);
        }
    }
}
