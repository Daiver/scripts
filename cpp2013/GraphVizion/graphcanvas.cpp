#include "graphcanvas.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/config.hpp>
#include <iterator>
#include <utility>

void GraphCanvas::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setBrush(Qt::black);
    p.drawEllipse(10, 10, 100, 100);
}

GraphCanvas::GraphCanvas()
{

}
