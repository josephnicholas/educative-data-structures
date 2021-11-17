#include <iostream>

#include "graph.hpp"

int main() {
    std::cout << "Hello, Graphs\n";
    
    auto graph = std::make_unique<Graph>(5);
    graph->add_edge(1, 2);
    graph->add_edge(1, 3);
    graph->add_edge(2, 4);
    graph->add_edge(2, 5);

    std::cout << "\n";

    graph->print_graph();
    return 0;
}