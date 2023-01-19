
#include <boost/graph/directed_graph.hpp> // A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
#include <boost//graph/graph_traits.hpp>
#include <vector>
#include <string.h>
#include <iostream>
#include <boost/graph/graph_utility.hpp>

#include <memory>
#include "boost/graph/random.hpp"
#include <random>

using namespace boost;
using namespace std;

#include "boost/graph/adjacency_list.hpp"
#include <boost/range/iterator_range.hpp>


void testRandom();

using Graph = boost::adjacency_list<>;
using V = Graph::vertex_descriptor;
using E = Graph::edge_descriptor;

E my_find_edge(V v, V u, Graph const& g)
{
    for (auto e : boost::make_iterator_range(out_edges(v, g))) {
        if (target(e, g) == u)
            return e;
    }
    throw std::domain_error("my_find_edge: not found");
}


void testRandom() {
    std::mt19937 prng{ std::random_device{}() };

    for (auto i = 0; i < 10; ++i)
        try {
        Graph g;
        generate_random_graph(g, 10, 20, prng);

        E e = my_find_edge(7, 2, g);
        std::cout << "Found: " << e << "\n";
    }
    catch (std::exception const& e) {
        std::cout << e.what() << "\n";
    }

    

}
