#include <unordered_map>
#include <vector>
#include <memory>
#include <chrono>
#include <cassert>

#include "binary_search_tree.hpp"

//void dfs(Node const *root, std::unordered_map<int, int> &levels, int level) {
//  auto current_node = root;
//
//  if (current_node != nullptr) {
//    if (levels.find(level) != levels.end()) {
//      levels[level] += current_node->value_;
//    } else {
//      levels[level] = current_node->value_;
//    }
//
//    dfs(current_node->left_, levels, level + 1);
//    dfs(current_node->right_, levels, level + 1);
//  }
//
//}
//
//std::vector<int> get_level_average(BinarySearchTree const* root) {
//  std::vector<int> result{};
//
//  return result;
//}
std::vector<int> bubbleSort(std::vector<int> array, int offset = 0) {
  // Write your code here.
  bool did_swap = false;
  for (int idx = 0; idx < array.size() - 1 - offset; idx++) {
    if (array[idx] > array[idx + 1])  {
      std::swap(array[idx], array[idx + 1]);
      did_swap = true;
    }
  }

  if (did_swap) {
    return bubbleSort(array, offset + 1);
  }

  return array;
}

std::vector<int> right_shift(std::vector<int> array, int offset = 0) {
  // take last element
  // to avoid it from overlapping
  // use it as the first element
  const auto last_element = array[array.size() - 1];
  for (auto idx = array.size() - 2; idx >= 0; idx--) {
    array[idx + 1] = array[idx];
  }

  array[0] = last_element;

  return array;
}
using namespace std;

#include <vector>
#include <iostream>
using namespace std;

// Do not edit the class below except for
// the insert, contains, and remove methods.
// Feel free to add new properties and methods
// to the class.
class BST {
 public:
  int value;
  BST *left;
  BST *right;
  BST *root;

  BST(int val) {
    value = val;
    left = nullptr;
    right = nullptr;
    root = this;
  }

  BST &insert(int val) {
    // node that we will be iterating over
    BST *current_node = root;

    // parent of the node that we will be iterating over
    BST *parent_node = current_node;

    while (current_node != nullptr) {
      // save the parent node.
      parent_node = current_node;
      if (val < current_node->value) {
        current_node = current_node->left;
      } else {
        current_node = current_node->right;
      }
    }

    // at this point we are at the parent_node of where we will
    // insert the new value.
    if (val < parent_node->value) {
      parent_node->left = new BST(val);
    } else {
      parent_node->right = new BST(val);
    }

    // Do not edit the return statement of this method.
    return *root;
  }

  bool contains(int val) {
    // Write your code here.
    BST *current_node = root;

    while(current_node != nullptr && val != current_node->value) {
      if (val < current_node->value) {
        current_node = current_node->left;
      } else {
        current_node = current_node->right;
      }
    }

    // at this point current_node will have the value that we have
    // or it's just null
    if (current_node != nullptr) {
      return true;
    }

    return false;
  }

  BST* smallest_node_right(BST* current_node) {
    if (current_node->left != nullptr) {
      return smallest_node_right(current_node->left);
    }

    return current_node;
  }

  BST &remove(int val) {
    // Write your code here.
    if (root == nullptr) {
      return *root;
    }
    BST *current_node = root;
    BST *parent_node = nullptr;

    // find the node to delete.
    while (current_node != nullptr && val != current_node->value) {
      parent_node = current_node;
      if (val < current_node->value) {
        current_node = current_node->left;
      } else {
        current_node = current_node->right;
      }
    }


    if (current_node == nullptr) /* not found */ {
      return *root;
    }
    else if (current_node->left == nullptr && current_node->right == nullptr) /* leaf node */ {
      if (root->value == current_node->value) {
        delete root;
        root = nullptr;
        return *root;
      } else if (val < parent_node->value) {
        delete parent_node->left;
        parent_node->left = nullptr;
        return *root;
      } else {
        delete parent_node->right;
        parent_node->right = nullptr;
        return *root;
      }
    } else if (current_node->left == nullptr) /* only right child */ {
      BST* right = current_node->right;
      if (root->value == current_node->value) {
        delete root;
        root = right;
        return *root;
      } else if (val < parent_node->value) {
        delete parent_node->left;
        parent_node->left = right;
        return *root;
      } else {
        delete parent_node->right;
        parent_node->right = right;
        return *root;
      }
    } else if (current_node->right == nullptr) /* only left child */ {
      BST* left = current_node->left;
      if (root->value == current_node->value) {
        delete root;
        root = left;
        return *root;
      } else if (val < parent_node->value) {
        delete parent_node->left;
        parent_node->left = left;
        return *root;
      } else {
        delete parent_node->right;
        parent_node->right = left;
        return *root;
      }
    } else /* has left and right child */ {
      // find the smallest node
      BST* smallest_node = smallest_node_right(current_node->right);
      int value = smallest_node->value;
      current_node->value = 0;
      remove(value);
      current_node->value = value;

      return *root;
    }
    // Do not edit the return statement of this method.
    return *root;
  }
};

int main(int argc, char* argv[]) {
  BST* root = new BST(10);
  root->insert(5);
  root->remove(10);
  assert(root->contains(5));
//  std::vector<int> nums{8, 5, 2, 9, 2, 7};
//  for (const auto &n : bubbleSort(nums)) {
//    std::cout << n << '\n';
//  }

//  std::vector<int> s{3, 2, 4, 1};
//  std::cout << "{ ";
//  for (const auto &n : right_shift(s)) {
//    std::cout << n << ',';
//  }
//  std::cout << "}\n ";

//  auto start = std::chrono::high_resolution_clock::now();
//  const auto tree = std::make_unique<BinarySearchTree<int>>(6);
//  tree->insert_node(4);
//  tree->insert_node(9);
//  tree->insert_node(2);
//  tree->insert_node(5);
//  tree->insert_node(8);
//  tree->insert_node(12);
//  tree->insert_node(10);
//  tree->insert_node(14);
//  auto end = std::chrono::high_resolution_clock::now();
//  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
//
//  std::cout << "Insertion time: " << duration.count() << "ns" << '\n';
//
//  tree->pre_order_traversal(tree->get_root());
//
//  assert(tree->delete_node(tree->get_root(), 9));
//  assert(tree->search_recursive(tree->get_root(), 9) == nullptr);
//  tree->pre_order_traversal(tree->get_root());
//  std::cout << '\n';
//
//  std::vector<int> flat{};
//  for (const auto n : tree->post_order_traversal(tree->get_root(), flat)){
//    std::cout << n << '\n';
//  }
//
//  std::cout << '\n';
//  std::vector<int> flat_in_order{};
//  for (const auto n : tree->in_order_traversal(tree->get_root(), flat_in_order)){
//    std::cout << n << '\n';
//  }
//  assert(tree->delete_node(tree->get_root(), 5) == true);
//  assert(tree->search_recursive(tree->get_root(), 5) != nullptr);
//  assert(tree->search_recursive(tree->get_root(), 700));

//  std::unordered_map<int, int> tree_sums{};
//  dfs(tree->get_root(), tree_sums, 0);
//
//  for (auto[k, v] : tree_sums) {
//    std::cout << "{" << k << ":" << v <<"}\n";
//  }

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