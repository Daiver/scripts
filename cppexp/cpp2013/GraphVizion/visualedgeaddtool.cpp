#include "visualedgeaddtool.h"

VisualEdgeAddTool::VisualEdgeAddTool()
{
    this->firstEdge = -1;
}

void VisualEdgeAddTool::mouseReleaseEvent(QMouseEvent *e, VisualGraph *g)
{
    int second_edge;
    if(this->firstEdge != -1 && (second_edge = g->getVertexIndexByCoo(graphvizion_td::Position(e->x(), e->y()))) != -1)
    {
        g->addEdge(this->firstEdge, second_edge);
    }
    this->firstEdge = -1;
}

void VisualEdgeAddTool::mouseMoveEvent(QMouseEvent *e, VisualGraph *g)
{
    if(this->firstEdge != -1)
    {
        this->mp = graphvizion_td::Position(e->x(), e->y());
    }
}

void VisualEdgeAddTool::mousePressEvent(QMouseEvent *e, VisualGraph *g)
{
    this->firstEdge = g->getVertexIndexByCoo(graphvizion_td::Position(e->x(), e->y()));
    if (this->firstEdge != -1)
    {
        this->mp = graphvizion_td::Position(
                    g->getByIndex(this->firstEdge).getPos().first,
                    g->getByIndex(this->firstEdge).getPos().second
                );
    }
}

void VisualEdgeAddTool::paintEvent(QPaintEvent *e, QPainter *painter, VisualGraph *g)
{
    if(this->firstEdge > -1)
    {
        painter->setBrush(Qt::black);
        painter->drawLine(
                        g->getByIndex(this->firstEdge).getPos().first,
                        g->getByIndex(this->firstEdge).getPos().second,
                        this->mp.first,
                        this->mp.second
                    );
    }
}
