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
    /*for (int i = 0; i < g->vertexes.size(); i++)
    {
        VisualVertex v = g->vertexes[i];
        if(sqrt(pow(e->x() - v.getPos().first, 2.0 ) + pow(e->y() - v.getPos().second, 2.0)) <= v.getSize())
        {
            qDebug("del %d", i);
            g->deleteByIndex(i);
        }
    }*/
}

void VisualVertexDeleteTool::paintEvent(QPaintEvent *e, QPainter *painter, VisualGraph *g)
{
}
