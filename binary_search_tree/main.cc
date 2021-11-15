#include <unordered_map>
#include <vector>
#include <memory>

#include "binary_search_tree.hpp"

void dfs(Node const *root, std::unordered_map<int, int> &levels, int level) {
  auto current_node = root;

  if (current_node != nullptr) {
    if (levels.find(level) != levels.end()) {
      levels[level] += current_node->value_;
    } else {
      levels[level] = current_node->value_;
    }

    dfs(current_node->left_, levels, level + 1);
    dfs(current_node->right_, levels, level + 1);
  }

}

std::vector<int> get_level_average(BinarySearchTree const* root) {
  std::vector<int> result{};

  return result;
}

int main(int argc, char* argv[]) {
  auto tree = std::make_unique<BinarySearchTree>(6);
  tree->insert_node(4);
  tree->insert_node(2);
  tree->insert_node(5);
  tree->insert_node(9);
  tree->insert_node(8);
  tree->insert_node(12);

//  tree->pre_order_traversal(tree->get_root());

  std::unordered_map<int, int> tree_sums{};
  dfs(tree->get_root(), tree_sums, 0);

  for (auto[k, v] : tree_sums) {
    std::cout << "{" << k << ":" << v <<"}\n";
  }

//  if (auto const node = tree->search_node(51)) {
//    std::cout << "Value: " << node->value_ << "\n";
//  } else {
//    std::cout << "Not Found!\n";
//  }
//
//  // delete leaf
//  if (auto const deleted = tree->delete_node(tree->get_root(), 40)) {
//    std::cout << "Deleted: " << 40 << "\n";
//  } else {
//    std::cout << "Failed to Delete!\n";
//  }
//
//  // after deletion
//  tree->pre_order_traversal(tree->get_root());

  return 0;
}