#include <iostream>
#include <string>

struct Node {
  int value_;
  Node* left_;
  Node* right_;

  Node() : value_(0), left_(nullptr), right_(nullptr) {}
  explicit Node(int value) : value_(value), left_(nullptr), right_(nullptr) {}
};

struct BinarySearchTree final : Node {
  Node* root_;

  BinarySearchTree() : root_(nullptr) {}
  explicit BinarySearchTree(int value) : root_(new Node(value)) {}

  Node* get_root() const noexcept { return root_; }

  // Insert
  void insert_node(int value) {
    if (get_root() == nullptr) {
      root_ = new BinarySearchTree(value);
      return;
    }

    Node* current_node = root_;
    Node* parent_node = new Node();

    while (current_node != nullptr) {
      parent_node = current_node;
      if (value < current_node->value_) {
        current_node = current_node->left_;
      } else {
        current_node = current_node->right_;
      }
    }

    // from this part we have a value for parent_node
    if (value < parent_node->value_) {
      parent_node->left_ = new Node(value);
    } else {
      parent_node->right_ = new Node(value);
    }
  }

  // Pre-order traversal
  // dfs like
  void pre_order_traversal(Node* current_node) const noexcept {
    if (current_node != nullptr) {
      std::cout << current_node->value_ << "\n";
      pre_order_traversal(current_node->left_);
      pre_order_traversal(current_node->right_);
    }
  }

  // Search
  // O(n) -> "n" is the number of nodes
  Node* search_node(int value) const noexcept {
    if (get_root() == nullptr) {
      return nullptr;
    }

    Node* current_node = root_;
    while (current_node != nullptr && value != current_node->value_) {
      if (value < current_node->value_) {
        current_node = current_node->left_;
      } else {
        current_node = current_node->right_;
      }
    }

    if (current_node != nullptr) {
      return current_node;
    }

    return nullptr;
  }

  // helper function to find the smallest node in the right subtree
  static Node* find_smallest_node(Node* current_node) {
    Node* temp_node = current_node;
    while (temp_node->left_ != nullptr) {
      temp_node = temp_node->left_;
    }

    // should have the smallest node in the right subtree
    return temp_node;
  }

  // Delete
  bool delete_node(Node* current_node, int value) {
    // empty list
    if (current_node == nullptr) {
      return false;
    }

    Node* parent_node = new Node();

    // find value in binary_search_tree
    while (current_node != nullptr && value != current_node->value_) {
      parent_node = current_node;
      if (value < current_node->value_) {
        current_node = current_node->left_;
      } else {
        current_node = current_node->right_;
      }
    }

    // if we didn't find the value
    if (current_node == nullptr) {
      return false;
    } else if (current_node->left_ == nullptr &&
               current_node->right_ == nullptr) /*leaf node*/ {
      if (root_->value_ == current_node->value_) {
        delete root_;
        root_ = nullptr;
        return true;
      } else if (value < parent_node->value_) {
        delete parent_node->left_;
        parent_node->left_ = nullptr;
        return true;
      } else {
        delete parent_node->right_;
        parent_node->right_ = nullptr;
        return true;
      }
    } else if (current_node->right_ == nullptr) /*node has left child only*/ {
      if (root_->value_ == current_node->value_) {
        delete root_;
        root_ = current_node->left_;
        return true;
      } else if (value < parent_node->value_) {
        delete parent_node->left_;
        parent_node->left_ = current_node->left_;
        return true;
      } else {
        delete parent_node->right_;
        parent_node->right_ = current_node->left_;
        return true;
      }
    } else if (current_node->left_ == nullptr) /*node has left child only*/ {
      if (root_->value_ == current_node->value_) {
        delete root_;
        root_ = current_node->right_;
        return true;
      } else if (value < parent_node->value_) {
        delete parent_node->left_;
        parent_node->left_ = current_node->right_;
        return true;
      } else {
        delete parent_node->right_;
        parent_node->right_ = current_node->right_;
        return true;
      }
    } else /* deleting node with 2 children */ {
      Node* smallest_node_right = find_smallest_node(current_node->right_);
      int val_of_smallest_node = smallest_node_right->value_;
      // Find and delete the that least smallest node.
      delete_node(
          root_,
          val_of_smallest_node);  // usually goes into delete lead node case
      // Switch the deleted node
      current_node->value_ = val_of_smallest_node;

      return true;
    }

    return false;
  }
};