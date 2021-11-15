// graph implementation - Adjacency list
// Contains two data members
//
// total_number_of_vertices
// list_of_linked_list -> to store adjacency vertices
#include <memory>
#include <vector>

#include "linkedlist.hpp"

class Graph final {
  int total_number_of_vertices{};

  // array of multiple linkedlist
  // should be equal to the number of vertices in the graph
  std::vector<LinkedList> array_of_linked_list{};

 public:
  explicit Graph(int vertices)
      : array_of_linked_list{std::vector<LinkedList>(vertices)},
        total_number_of_vertices{vertices} {}

  void add_edge(int source, int destination) {
    if (source < total_number_of_vertices &&
        destination < total_number_of_vertices) {
      array_of_linked_list[source].insert_at_head(destination);
      // for undirected graphs we will have
      //      array_of_linked_list[destination].insert_at_head(source);
    }
  }

  void print_graph() const {
    std::cout << "Adjacency List of Directed graph\n";
    Node *temp_node;

    for (int i = 0; i < total_number_of_vertices; i++) {
      std::cout << "|" << i << "| => ";
      temp_node = array_of_linked_list[i].get_head();

      while (temp_node != nullptr) {
        std::cout << "[" << temp_node->get_node_data() << "] -> ";
        temp_node = temp_node->get_next_node();
      }
      std::cout << "NULL\n";
    }
  }
};