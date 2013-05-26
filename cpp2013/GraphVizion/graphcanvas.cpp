#include <QDebug>
#include <QString>

#include "graphcanvas.h"
#include <utility>
#include "visualvertexaddtool.h"
#include "visualvertexmovetool.h"
#include "visualvertexdeletetool.h"
#include "visualedgeaddtool.h"

void GraphCanvas::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if (nullptr != this->tool)
    {
        this->tool->paintEvent(e, &p, &this->VG);
    }
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
    this->tool = nullptr;
}

void GraphCanvas::setVertexAddTool()
{
    if(nullptr != this->tool)
        delete this->tool;
    this->tool = new VisualVertexAddTool();
}

void GraphCanvas::setVertexMoveTool()
{
    if(nullptr != this->tool)
        delete this->tool;
    this->tool = new VisualVertexMoveTool();
}

void GraphCanvas::setVertexDeleteTool()
{
    if(nullptr != this->tool)
        delete this->tool;
    this->tool = new VisualVertexDeleteTool();
}

void GraphCanvas::setEdgeAddTool()
{
    if(nullptr != this->tool)
        delete this->tool;
    this->tool = new VisualEdgeAddTool();
}


void GraphCanvas::mousePressEvent(QMouseEvent *e)
{
    if(nullptr != this->tool)
        this->tool->mousePressEvent(e, &this->VG);
    this->repaint();
}


void GraphCanvas::mouseMoveEvent(QMouseEvent *e)
{
    if(nullptr != this->tool)
        this->tool->mouseMoveEvent(e, &this->VG);
    this->repaint();
}

void GraphCanvas::mouseReleaseEvent(QMouseEvent *e)
{
    if(nullptr != this->tool)
        this->tool->mouseReleaseEvent(e, &this->VG);
    this->repaint();
}
