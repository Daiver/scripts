#include "visualgraph.h"
#include <queue>

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
    boost::graph_traits<graphvizion_td::Graph>::edge_iterator iter;
    boost::graph_traits<graphvizion_td::Graph>::adjacency_iterator ei, ei_end;
    graphvizion_td::IndexMap index = boost::get(boost::vertex_index, this->graph);
    //std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp;
    //for (vp = boost::vertices(this->VG.graph); vp.first != vp.second; ++vp.first)
    //{

    //}

    /*
     * graph_traits < adjacency_list <> >::vertex_iterator i, end;
  graph_traits < adjacency_list <> >::adjacency_iterator ai, a_end;
  property_map < adjacency_list <>, vertex_index_t >::type
    index_map = get(vertex_index, g);

  for (tie(i, end) = vertices(g); i != end; ++i) {
    std::cout << name[get(index_map, *i)];
    tie(ai, a_end) = adjacent_vertices(*i, g);
    if (ai == a_end)
      std::cout << " has no children";
    else
      std::cout << " is the parent of ";
    for (; ai != a_end; ++ai) {
      std::cout << name[get(index_map, *ai)];
      if (boost::next(ai) != a_end)
        std::cout << ", ";
    }
    std::cout << std::endl;
  }
    */
}
