#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

template <typename T>
struct Node final {
  T value_;
  std::unique_ptr<Node> left_;   // pointer to the left node
  std::unique_ptr<Node> right_;  // pointer to the right node
  uint32_t count_;               // keeping track of nodes that are duplicates

  Node() : value_({}), left_(nullptr), right_(nullptr), count_(0) {}

  explicit Node(int value)
      : value_(value), left_(nullptr), right_(nullptr), count_(1) {}
};

template <typename T>
struct BinarySearchTree final {
  std::unique_ptr<Node<T>> root_;

  BinarySearchTree() : root_(nullptr) {}

  explicit BinarySearchTree(int value)
      : root_(std::make_unique<Node<T>>(value)) {}

  [[nodiscard]] Node<T> *get_root() const noexcept { return root_.get(); }

  [[nodiscard]] bool operator==(BinarySearchTree<T> *rhs) const noexcept {
    std::vector<T> flatten{};
    std::vector<T> flatten_right{};

    in_order_traversal(get_root(), flatten);
    in_order_traversal(rhs->get_root(), flatten_right);

    return flatten == flatten_right;
  }

  [[nodiscard]] int height(Node<T> *current_node) const noexcept {
    // if we are in an empty node we don't count it as part
    // of the height. Height of the last non-empty node is zero
    if (current_node == nullptr) /* empty */ {
      return -1;
    }

    if (current_node->left_ == nullptr && current_node->right_ == nullptr) {
      return 0;
    }

    return std::max(1 + height(current_node->left_.get()),
                    1 + height(current_node->right_.get()));
  }

  [[nodiscard]] int balance_factor() const noexcept {
    // we get the height of the left and right subarray
    // we add 1 to them assuming we already counted the root_node in
    // height(root_node)
    const Node<T> *current_node = get_root();
    const int left_height = 1 + height(current_node->left_.get());
    const int right_height = 1 + height(current_node->right_.get());

    return std::abs(left_height - right_height);
  }

  /**
   * Inserts a node into the BST
   * @param value
   */
  void insert_node(T value) {
    // Create a new node if the BST is empty
    if (get_root() == nullptr) {
      root_ = std::make_unique<Node<T>>(value);
      return;
    }

    // get the pointer of the current node
    Node<T> *current_node = get_root();

    // add a pointer to the parent node
    // at this point it's NULL
    Node<T> *parent_node{nullptr};

    // keep on traversing until the current_node is already null/empty
    while (current_node != nullptr) {
      // update the parent node, this will act as the parent
      // of the inserted nodes
      parent_node = current_node;
      // if value is less than the current node value; update current_node to
      // move left otherwise; update current_node to move right
      if (value == current_node->value_) {
        current_node->count_++;
        return;
      } else if (value < current_node->value_) {
        current_node = current_node->left_.get();
      } else {
        current_node = current_node->right_.get();
      }
    }

    // at this point we are on the parent node which has, 1 or empty child nodes
    // we insert the new node to that empty/null child.
    if (value < parent_node->value_) {
      parent_node->left_ = std::make_unique<Node<T>>(value);
    } else {
      parent_node->right_ = std::make_unique<Node<T>>(value);
    }
  }

  // Pre-order traversal
  // dfs like
  void pre_order_traversal(Node<T> *current_node) const noexcept {
    if (current_node != nullptr) {
      std::cout << current_node->value_ << "\n";
      pre_order_traversal(current_node->left_.get());
      pre_order_traversal(current_node->right_.get());
    }
  }

  void post_order_traversal(Node<T> *current_node,
                            std::vector<T> &flat_tree) const noexcept {
    if (current_node != nullptr) {
      post_order_traversal(current_node->left_.get(), flat_tree);
      post_order_traversal(current_node->right_.get(), flat_tree);
      flat_tree.push_back(current_node->value_);
    }
  }

  void in_order_traversal(Node<T> *current_node,
                          std::vector<T> &flat_tree) const noexcept {
    if (current_node != nullptr) {
      in_order_traversal(current_node->left_.get(), flat_tree);
      flat_tree.push_back(current_node->value_);
      in_order_traversal(current_node->right_.get(), flat_tree);
    }
  }

  /**
   * Iteratively searches the element in the three
   *
   * O(n) - worst case
   *
   * @param value
   * @return
   */
  Node<T> *search_node(T value) const noexcept {
    // if BST is empty then return nullptr
    if (get_root() == nullptr) {
      return nullptr;
    }

    // set the current node to be the root node
    // and start traversing
    Node<T> *current_node = root_.get();

    // traverse the tree if the current node isn't a nullptr
    // and if the value isn't the value we're looking for
    while (current_node != nullptr && value != current_node->value_) {
      // if value is less than the current node's value
      // we move left, otherwise right
      if (value < current_node->value_) {
        current_node = current_node->left_.get();
      } else {
        current_node = current_node->right_.get();
      }
    }

    // at this point we are pointing to the node we searched for
    if (current_node != nullptr) {
      return current_node;
    }

    return nullptr;
  }

  /**
   * Recursively searches for an element in the tree
   *
   * @param current_node
   * @param value
   * @return
   */
  static Node<T> *search_recursive(Node<T> *current_node, T value) noexcept {
    if (current_node == nullptr) {
      return nullptr;
    }

    if (value == current_node->value_) {
      return current_node;
    }

    if (value < current_node->value_) {
      return search_recursive(current_node->left_.get(), value);
    } else {
      return search_recursive(current_node->right_.get(), value);
    }
  }

  static Node<T> *find_smallest_node_right_subtree(
      Node<T> *current_node) noexcept {
    if (current_node->left_ != nullptr) {
      return find_smallest_node_right_subtree(current_node->left_.get());
    }

    return current_node;
  }

  /**
   * Delete a node in the tree
   *
   * @param current_node
   * @param value
   * @return
   */
  bool delete_node(Node<T> *current_node, T value) noexcept {
    // 1. Delete a node in an empty tree
    if (current_node == nullptr) {
      return false;
    }

    // parent node
    Node<T> *parent_node = nullptr;

    // search for the element
    // need to implement search here since we need to update
    // the parent node
    while (current_node != nullptr && value != current_node->value_) {
      parent_node = current_node;
      if (value < current_node->value_) {
        current_node = current_node->left_.get();
      } else {
        current_node = current_node->right_.get();
      }
    }

    if (current_node->count_ > 1) {
      current_node->count_--;
      return true;
    }

    // if we didn't find what we're looking for
    if (current_node == nullptr) {
      return false;
    } else if (current_node->left_ == nullptr &&
               current_node->right_ == nullptr) /* leaf node */ {
      std::cout << "delete leaf only!\n";
      // additional constraint if the BST has only a root node
      if (nullptr == parent_node) {
        root_ = nullptr;
      }

      if (value < parent_node->value_) {
        // point the parent node's left to nullptr
        // this will also clean up the unique_ptr
        parent_node->left_ = nullptr;
      } else {
        // point the parent node's left to nullptr
        // this will also clean up the unique_ptr
        parent_node->right_ = nullptr;
      }
    } else if (current_node->right_ == nullptr) /* left child only */ {
      std::cout << "left child only!\n";
      // depending on the value constraints
      // we must overwrite the node that we deleted with its child node
      // overwriting in turn will remove the previous Node object
      if (nullptr == parent_node) {
        current_node->value_ = std::move(current_node->left_->value_);
        current_node->right_ = std::move(current_node->left_->right_);
        current_node->left_ = std::move(current_node->left_->left_);
      } else if (value < parent_node->value_) {
        parent_node->left_ = std::move(current_node->left_);
      } else {
        parent_node->right_ = std::move(current_node->left_);
      }
    } else if (current_node->left_ == nullptr) /* right child only */ {
      std::cout << "right child only!\n";
      // depending on the value constraints
      // we must overwrite the node that we deleted with its child node
      // overwriting in turn will remove the previous Node object
      if (nullptr == parent_node) {
        current_node->value_ = std::move(current_node->right_->value_);
        current_node->right_ = std::move(current_node->right_->right_);
        current_node->left_ = std::move(current_node->right_->left_);
      } else if (value < parent_node->value_) {
        parent_node->left_ = std::move(current_node->right_);
      } else {
        parent_node->right_ = std::move(current_node->right_);
      }
    } else /* has 2 children */ {
      std::cout << "2 children\n";
      // find the smallest node in the right subtree
      Node<T> *smallest_node =
          find_smallest_node_right_subtree(current_node->right_.get());
      const auto value_of_smallest_node = smallest_node->value_;
      // delete the smallest node in the right subtree
      // in the context of current_node
      std::ignore = delete_node(root_.get(), value_of_smallest_node);

      // replace the "value to be deleted" with the smallest value
      current_node->value_ = value_of_smallest_node;
    }

    return true;
  }

  void dfs(Node<T> *root, std::unordered_map<int, int> &levels,
           int level) const noexcept {
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
};