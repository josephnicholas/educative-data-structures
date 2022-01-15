#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>

#include "graph.hpp"

// O(V + E)
auto bfs_traversal(const Graph &graph) {
  auto adjacency_list = graph.get_adjacency_list();
  std::unordered_set<int> visited_set{};
  std::queue<int> to_visit_queue{};
  std::string result;

  for (int source = 0; source < adjacency_list.size(); source++) {
    if (!visited_set.insert(source).second) {
      continue;
    }

    to_visit_queue.emplace(source);

    while (!to_visit_queue.empty()) {
      auto adjacency_list_current_node = to_visit_queue.front();
      to_visit_queue.pop();

      result += std::to_string(adjacency_list_current_node);

      if (!adjacency_list[adjacency_list_current_node].is_empty()) {
        auto current_node =
            adjacency_list[adjacency_list_current_node].get_head();

        while (current_node != nullptr) {
          if (visited_set.insert(current_node->get_node_data()).second) {
            to_visit_queue.emplace(current_node->get_node_data());
          }

          current_node = current_node->get_next_node();
        }
      }
    }
  }

  return result;
}

// O(V+E)
auto dfs_traversal(const Graph &graph) {
  auto adjacency_list = graph.get_adjacency_list();
  std::unordered_set<int> visited_set{};
  std::stack<int> to_visit_stack{};

  std::string result;

  for (int source = 0; source < adjacency_list.size(); source++) {
    if (!visited_set.insert(source).second) {
      continue;
    }

    to_visit_stack.emplace(source);

    while (!to_visit_stack.empty()) {
      auto adjacency_list_current_node = to_visit_stack.top();
      to_visit_stack.pop();

      result += std::to_string(adjacency_list_current_node);

      if (!adjacency_list[adjacency_list_current_node].is_empty()) {
        auto current_node =
            adjacency_list[adjacency_list_current_node].get_head();

        while (current_node != nullptr) {
          if (visited_set.insert(current_node->get_node_data()).second) {
            to_visit_stack.emplace(current_node->get_node_data());
          }

          current_node = current_node->get_next_node();
        }
      }
    }
  }

  return result;
}

//O(V + E)
// but maybe O(V(V + E))
[[maybe_unused]] [[nodiscard]] int find_mother_vertex(const Graph &graph) {
  if (graph.get_total_number_of_vertices() < 1) {
    return -1;
  }

  std::unordered_set<int> already_visited_nodes{};
  std::stack<int> nodes_to_visit{};

  auto adjacency_list = graph.get_adjacency_list();

  for (int source = 0; source < adjacency_list.size(); source++) {
    if (!already_visited_nodes.empty()) {
      // this means that the set of visited nodes
      // does not match the number of vertices.
      already_visited_nodes.clear();
    }

    nodes_to_visit.emplace(source);

    while(!nodes_to_visit.empty()) {
      auto current_visited_node = nodes_to_visit.top();
      nodes_to_visit.pop();

      already_visited_nodes.emplace(current_visited_node);

      Node* adjacent_node = adjacency_list[current_visited_node].get_head();
      while (adjacent_node != nullptr) {
        if(!already_visited_nodes.emplace(adjacent_node->get_node_data()).second) {
          break;
        }
        nodes_to_visit.emplace(adjacent_node->get_node_data());
        adjacent_node = adjacent_node->get_next_node();
      }

    }

    if (already_visited_nodes.size() == graph.get_total_number_of_vertices()) {
      return source;
    }
  }

  return -1;
}

int num_edges(const Graph &graph) {
  return 0;
}

int main() {
  std::cout << "Hello, Graphs\n";

  //  auto graph = std::make_unique<Graph>(4);
  //  graph->add_edge_directed(0, 1);
  //  graph->add_edge_directed(0, 2);
  //  graph->add_edge_directed(1, 3);
  //  graph->add_edge_directed(2, 3);
  //
  //  std::cout << "\n";
  //
  //  graph->print_graph();
  //
  //  std::cout << "\n";
  //  const auto graph_undirected = std::make_unique<Graph>(4);
  //  graph_undirected->add_edge_undirected(0, 1);
  //  graph_undirected->add_edge_undirected(0, 2);
  //  graph_undirected->add_edge_undirected(1, 3);
  //  graph_undirected->add_edge_undirected(2, 3);
  //
  //  std::cout << "\n";
  //
  //  graph_undirected->print_graph();
  //
  auto graph_bfs = std::make_unique<Graph>(7);
  graph_bfs->add_edge_directed(1, 2);
  graph_bfs->add_edge_directed(1, 3);
  graph_bfs->add_edge_directed(1, 4);
  graph_bfs->add_edge_directed(4, 5);
  graph_bfs->add_edge_directed(4, 6);

  std::cout << "\n";

  std::ignore = graph_bfs->print_graph();

  std::cout << "\n";

  for (const auto result : bfs_traversal(*graph_bfs)) {
    std::cout << result << "->";
  }

  std::cout << "\n===dfs===\n";

  auto graph_dfs = std::make_unique<Graph>(5);
  graph_dfs->add_edge_directed(0, 1);
  graph_dfs->add_edge_directed(0, 2);
  graph_dfs->add_edge_directed(1, 4);
  graph_dfs->add_edge_directed(1, 5);

  std::ignore = graph_dfs->print_graph();

  for (const auto result : dfs_traversal(*graph_dfs)) {
    std::cout << result << "->";
  }


  std::cout << "\n===mother_node===\n";

  auto graph_mother_node = std::make_unique<Graph>(4);
  graph_mother_node->add_edge_directed(0, 1);
  graph_mother_node->add_edge_directed(1, 2);
  graph_mother_node->add_edge_directed(3, 0);
  graph_mother_node->add_edge_directed(3, 1);

  std::ignore = graph_mother_node->print_graph();

  std::cout << find_mother_vertex(*graph_mother_node) << "\n";

  return 0;
}

/**
* recursive call
 *
 *
 * #include "Graph.h"

using namespace std;

// Recursive function
bool detectCycleRec(Graph g, int i, bool* visited, bool* recNodes) {
  // Check if current node is being visited in the same recursive call

  if(visited[i]==false) {
    // Set recursive array and visited to true
    visited[i] = true;
    recNodes[i] = true;

    int adjacent;
    Node* adjacentNode=(g.getArray())[i].getHead();
    while (adjacentNode != NULL ) {
      // Access adjacent node and repeat algorithm
      adjacent = adjacentNode->data;
      if ((!visited[adjacent]) && detectCycleRec(g, adjacent, visited, recNodes))
        return true;  // Loop found
      else if(recNodes[adjacent])
        return true;
      adjacentNode=adjacentNode->nextElement;
    }

  }


  recNodes[i] = false;
  return false;
}
bool detectCycle(Graph g) {

  int num_of_vertices = g.getVertices();
  //Boolean Array to hold the history of visited nodes (by default-false)
  //Make a node visited whenever you traverse it
  bool* visited = new bool[num_of_vertices];

  //Boolean array of vertices which will recursively called
  bool* recNodes = new bool[num_of_vertices];

  for(int i = 0; i < num_of_vertices; i++)
  {
    visited[i] = false;
    recNodes[i] = false;
  }

  for (int i = 0; i < num_of_vertices; i++) { // Recursive function called
    if (detectCycleRec(g,i, visited, recNodes))
      return true;
    // If cycle detected, return true
  }
  return false;
}

int main() {

  Graph g(6);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(3, 4);
  g.addEdge(4, 5);
  cout << detectCycle(g) << endl;
  g.addEdge(5, 3);
  cout << detectCycle(g) << endl;
}
*/

/* Mother vertex
  //A recursive function to print DFS starting from v
void DFS(Graph g, int node, bool* visited) {

// Mark the current node as visited and print it
visited[node] = true;

// Recur for all the vertices adjacent to this vertex
Node* temp = (g.getArray())[node].getHead();
while(temp) {
if (visited[temp->data] == false)
  DFS(g, temp->data, visited);
temp = temp->nextElement;
}
}
int findMotherVertex(Graph g) {
//visited[] is used for DFS. Initially all are
// initialized as not visited

bool* visited = new bool[g.getVertices()];
//To store last finished vertex (or mother vertex)
int lastV=0;

//Do a DFS traversal and find the last finished vertex
for (int i = 0; i < g.getVertices(); i++) {
  if(visited[i]==false) {
    DFS(g, i, visited);
    lastV = i;
  }
}


// If there exist mother vertex (or vetices) in given graph, then v must be one (or one of them)
// Now check if v is actually a mother vertex (or graph has a mother vertex).
//We basically check if every vertex is reachable from v or not.

//Reset all values in visited[] as false and do
//DFS beginning from v to check if all vertices are
//reachable from it or not.

for (int i = 0; i < g.getVertices(); i++)
{
  visited[i]=false;

}

DFS(g, lastV, visited);
for (int i = 0; i < g.getVertices(); i++) {
  if(visited[i]==false)
    return -1;

}
delete[] visited;
visited = NULL;
return lastV;

}

 */