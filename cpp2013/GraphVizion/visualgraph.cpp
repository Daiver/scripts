#include "visualgraph.h"


VisualGraph::VisualGraph()
{
    this->index = boost::get(boost::vertex_index, this->graph);
}

void VisualGraph::addVertex(VisualVertex vertex)
{
    boost::add_vertex(this->graph);
    this->vertexes.push_back(vertex);
}

VisualVertex &VisualGraph::getByIndex(int i)
{
    return this->vertexes[i];
}

VisualVertex &VisualGraph::getByIterator(std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp)
{
    return this->getByIndex(this->index[*vp.first]);
}

bool VisualGraph::deleteByIndex(int i)
{
    if (i >= this->vertexes.size() || i < 0) return false;
    boost::remove_vertex(this->index[0], this->graph);
    this->vertexes.erase(this->vertexes.begin() + i);
    return true;
}

void VisualGraph::addEdge(int first, int second)
{
    boost::add_edge(first, second, this->graph);
}

VisualVertex *VisualGraph::getVertexByCoo(graphvizion_td::Position pos)
{
    VisualVertex* res = nullptr;
    std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp;
    for (vp = boost::vertices(this->graph); vp.first != vp.second; ++vp.first)
    {
        VisualVertex v = this->getByIterator(vp); //getByIndex(index[*vp.first]);
        if(sqrt(pow(pos.first - v.getPos().first, 2.0 ) + pow(pos.second - v.getPos().second, 2.0)) <= v.getSize())
        {
            res = &this->getByIterator(vp);
        }
    }
    return res;
}

int VisualGraph::getVertexIndexByCoo(graphvizion_td::Position pos)
{
    for (int i = 0; i < this->vertexes.size(); i++)
    {
        VisualVertex v = this->vertexes[i];
        if(sqrt(pow(pos.first - v.getPos().first, 2.0 ) + pow(pos.second - v.getPos().second, 2.0)) <= v.getSize())
        {
            return i;
        }
    }
    return -1;
}
