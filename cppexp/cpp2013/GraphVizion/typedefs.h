#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <list>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/config.hpp>
#include <iterator>

namespace graphvizion_td
{
    typedef boost::adjacency_list<boost::listS, boost::vecS> Graph; // VertexList=vecS
    typedef std::pair<int, int> Edge;
    typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    typedef std::pair<int, int> Position;
}
#endif // TYPEDEFS_H
