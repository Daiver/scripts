#include "graphcanvas.h"
#include <iostream>
#include <utility>

void GraphCanvas::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setBrush(Qt::black);
    //this->VG.addVertex(VisualVertex(graphvizion_td::Position(30, 10)));
    std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp;
    for (vp = boost::vertices(this->VG.graph); vp.first != vp.second; ++vp.first)
    {
        auto v = this->VG.getByIterator(vp); //getByIndex(index[*vp.first]);
        p.drawEllipse(v.getPos().first, v.getPos().second, 10, 10);
    }
}

GraphCanvas::GraphCanvas()
{    
    this->VG.addVertex(VisualVertex(graphvizion_td::Position(10, 10)));
    this->VG.addVertex(VisualVertex(graphvizion_td::Position(20, 20)));
    this->VG.addVertex(VisualVertex(graphvizion_td::Position(200, 30)));
    boost::add_edge(0, 1, this->VG.graph);
}
