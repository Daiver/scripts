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
    if (i >= this->vertexes.size()) return false;
    boost::remove_vertex(this->index[0], this->graph);
    this->vertexes.erase(this->vertexes.begin() + i);
    return true;
}
