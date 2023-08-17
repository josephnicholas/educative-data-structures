// graph implementation - Adjacency list
// Contains two data members
//
// total_number_of_vertices
// list_of_linked_list -> to store adjacency vertices
#include <memory>
#include <vector>

#include "linkedlist.hpp"

template <typename T>
class Graph final {
  int total_number_of_vertices_{};

  // array of multiple linkedlist
  // should be equal to the number of vertices in the graph
  std::vector<LinkedList<T>> array_of_linked_list_{};

 public:
  explicit Graph(int vertices)
      : array_of_linked_list_{std::vector<LinkedList<T>>(vertices)},
        total_number_of_vertices_{vertices} {}

  [[maybe_unused]] inline void add_edge_directed(int source, int destination) {
    if (source < total_number_of_vertices_ &&
        destination < total_number_of_vertices_) {
      array_of_linked_list_[source].insert_at_head(destination);
    }
  }

  [[maybe_unused]] inline void add_edge_undirected(int source,
                                                   int destination) {
    if (source < total_number_of_vertices_ &&
        destination < total_number_of_vertices_) {
      array_of_linked_list_[source].insert_at_head(destination);
      array_of_linked_list_[destination].insert_at_head(source);
    }
  }

  [[maybe_unused]] [[nodiscard]] inline auto get_adjacency_list()
      const noexcept {
    return array_of_linked_list_;
  }

  [[maybe_unused]] [[nodiscard]] inline auto get_total_number_of_vertices()
      const noexcept {
    return total_number_of_vertices_;
  }

  [[nodiscard]] inline bool print_graph() const noexcept {
    if (this->total_number_of_vertices_ == 0) {
      return false;
    }

    std::cout << "Adjacency List of Directed graph\n";
    std::shared_ptr<Node<T>> temp_node;

    for (int i = 0; i < total_number_of_vertices_; i++) {
      std::cout << "|" << i << "| => ";
      temp_node = array_of_linked_list_[i].get_head();

      while (temp_node != nullptr) {
        std::cout << "[" << temp_node->get_node_data() << "] -> ";
        temp_node = std::move(temp_node->get_next_node());
      }
      std::cout << "NULL\n";
    }

    return true;
  }
};