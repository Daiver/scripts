#include "visualgraph.h"
#include <queue>
#include <QString>

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
    boost::remove_vertex(this->index[i], this->graph);
    this->vertexes.erase(this->vertexes.begin() + i);
    return true;
}

void VisualGraph::addEdge(int first, int second)
{
    boost::add_edge(first, second, this->graph);
    boost::add_edge(second, first, this->graph);
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

void VisualGraph::markVertex(int startindex)
{

    graphvizion_td::IndexMap index = boost::get(boost::vertex_index, this->graph);
    boost::graph_traits<graphvizion_td::Graph>::adjacency_iterator ei, ei_end;
    //std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp;
    std::queue< std::pair<decltype(*ei), int> > queue;
    //vp = boost::vertices(this->graph);

    queue.push(std::pair<decltype(*ei), int>(index[startindex], 0));
    std::vector<bool> isWalked(this->vertexes.size());
    while(!queue.empty())
    {
        auto pair = queue.front();
        auto desc = pair.first;
        int num = pair.second;
        queue.pop();
        if(isWalked[desc]) continue;
        isWalked[desc] = true;
        this->vertexes[(int)desc].setLabel(QString("%1").arg(num));
        num++;
        boost::tie(ei, ei_end) = boost::adjacent_vertices(desc, this->graph);
        for(; ei != ei_end; ei++)
        {
            queue.push(std::pair<decltype(*ei), int>(*ei, num));
        }
    }
}
