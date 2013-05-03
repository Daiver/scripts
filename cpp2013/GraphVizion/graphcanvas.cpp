#include "graphcanvas.h"

#include <iostream>

#include <utility>

void GraphCanvas::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setBrush(Qt::black);
    p.drawEllipse(10, 10, 100, 100);
}

GraphCanvas::GraphCanvas()
{
    Graph g(10);
    boost::add_vertex(g);
    boost::add_vertex(g);
    boost::add_edge(0, 1, g);
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = boost::vertices(g); vp.first != vp.second; ++vp.first)
    {
        auto x = vp.first;
    }
}
