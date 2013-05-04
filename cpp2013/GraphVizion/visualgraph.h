#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

#include "typedefs.h"
#include "visualvertex.h"

#include <vector>

class VisualGraph
{
public:
    VisualGraph();
    void addVertex(VisualVertex vertex);
    VisualVertex& getByIndex(int i);
    VisualVertex &getByIterator(std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp);
    bool deleteByIndex(int i);


    graphvizion_td::Graph graph;
    std::vector<VisualVertex> vertexes;
    graphvizion_td::IndexMap index;
};

#endif // VISUALGRAPH_H
