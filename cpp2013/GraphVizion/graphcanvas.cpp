#include "graphcanvas.h"
#include <iostream>
#include <utility>

void GraphCanvas::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    graphvizion_td::IndexMap index = boost::get(boost::vertex_index, this->VG.graph);
    p.setBrush(Qt::black);
    boost::graph_traits<graphvizion_td::Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(this->VG.graph); ei != ei_end; ++ei)
    {
        p.drawLine(this->VG.getByIndex(index[source(*ei, this->VG.graph)]).getPos().first,
                this->VG.getByIndex(index[source(*ei, this->VG.graph)]).getPos().second,
                this->VG.getByIndex(index[target(*ei, this->VG.graph)]).getPos().first,
                this->VG.getByIndex(index[target(*ei, this->VG.graph)]).getPos().second);
    }
    p.setBrush(Qt::green);
    std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp;
    for (vp = boost::vertices(this->VG.graph); vp.first != vp.second; ++vp.first)
    {
        auto v = this->VG.getByIterator(vp); //getByIndex(index[*vp.first]);
        p.drawEllipse(v.getPos().first - v.getSize()/2, v.getPos().second - v.getSize()/2, v.getSize(), v.getSize());
    }


}

GraphCanvas::GraphCanvas()
{    
    this->VG.addVertex(VisualVertex(graphvizion_td::Position(10, 10)));
    this->VG.addVertex(VisualVertex(graphvizion_td::Position(20, 20)));
    this->VG.addVertex(VisualVertex(graphvizion_td::Position(200, 30)));
    boost::add_edge(0, 2, this->VG.graph);
}
