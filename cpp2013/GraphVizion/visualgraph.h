#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

#include "typedefs.h"
#include "visualvertex.h"

#include <vector>

class GraphCanvas;//TODO

class VisualGraph
{
friend class GraphCanvas;
public:
    VisualGraph();
    void addVertex(VisualVertex vertex);
    VisualVertex& getByIndex(int i);
    VisualVertex &getByIterator(std::pair<graphvizion_td::vertex_iter, graphvizion_td::vertex_iter> vp);
    bool deleteByIndex(int i);

    void addEdge(int first, int second);

    VisualVertex* getVertexByCoo(graphvizion_td::Position pos);
    int getVertexIndexByCoo(graphvizion_td::Position pos);

protected:
    graphvizion_td::Graph graph;
    std::vector<VisualVertex> vertexes;
    graphvizion_td::IndexMap index;
};

#endif // VISUALGRAPH_H
