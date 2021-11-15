#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

static constexpr int ALPHABET_LENGTH = 26;
/// TrieNode represents each alphabet

struct TrieNode {
  TrieNode() {
    this->is_end_of_node_ = false;
    set_initial_node_value();
  }

  inline void set_initial_node_value() {
    for (auto& child_node : this->children_) {
      child_node = nullptr;
    }
  }

  inline void mark_as_leaf() { this->is_end_of_node_ = true; }

  inline void unmark_as_leaf() { this->is_end_of_node_ = false; }

  std::array<TrieNode*, ALPHABET_LENGTH>
      children_{};                 // array of pointers to children nodes
  bool is_end_of_node_ = false;  // boolean mark as end of the word.
};

struct Trie final : TrieNode {
  Trie() { root_node_ = new TrieNode(); }

  static inline int get_index(char t) {
    // returns the index of the character
    // a == 0
    // b == 1
    // .. z == 26
    return t - 'a';
  }

  /// Time Complexity O(n)
  /// n = number of characters to be inserted
  inline bool insert_node(std::string key) {
    // Empty string is not allowed
    if (key.empty()) {
      return false;
    }

    // transform to lower all characters in the string
    std::transform(key.begin(), key.end(), key.begin(),
                   [&](char c) { return std::tolower(c); });

    TrieNode* current_node = root_node_;
    int index{};

    for (int level = 0; level < key.size(); level++) {
      index = get_index(key[level]);

      if (current_node->children_[index] == nullptr) {
        current_node->children_[index] = new TrieNode();
        std::cout << "inserted: " << key[level] << "\n";
      }

      // Update current_node to the next node to insert or iterate through if
      // char is already present
      current_node = current_node->children_[index];
    }

    // after end of insert mark TrieNode as end.
    current_node->mark_as_leaf();
    std::cout << key << " inserted!\n";
    return true;
  }

  inline bool construct_trie(std::vector<std::string> const& keys) {
    if (keys.empty()) {
      return false;
    }

    for (auto const& key : keys) {
      if (!insert_node(key)) {
        std::cout << "Failed to insert: " << key << "\n";
        return false;
      }
    }
    return true;
  }

  // Time complexity: O(h)
  // where "h" is the length of the key
  // each level would consider another character to find
  inline bool search_node(std::string key) {
    if (key.empty()) {
      return false;
    }

    // transform to lower all characters in the string
    std::transform(key.begin(), key.end(), key.begin(),
                   [&](char c) { return std::tolower(c); });

    TrieNode* current_node = root_node_;
    int index_of_char;

    for (int level_of_trie = 0; level_of_trie < key.size(); level_of_trie++) {
      index_of_char = get_index(key[level_of_trie]);

      // first letter isn't found return false
      if (current_node->children_[index_of_char] == nullptr) {
        return false;
      }
      current_node = current_node->children_[index_of_char];
    }

    if (current_node != nullptr && current_node->is_end_of_node_) {
      return true;
    }

    return false;
  }

  inline std::vector<std::string> search_by_prefix(const std::string &key) {
    if (key.empty()) {
      return {};
    }

    TrieNode* current_node = root_node_;
    int index_of_char;

    for(int level_of_trie = 0; level_of_trie < key.size(); level_of_trie++) {
      index_of_char = get_index(key[level_of_trie]);

      if (current_node->children_[index_of_char] == nullptr) {
        return {};
      }

      current_node = current_node->children_[index_of_char];
    }

    return find_all_words(current_node, key.data());
  }

  // O(n)
  // n = number of trie nodes
  void get_words_and_store(TrieNode *root_node, std::vector<std::string> &result,
                           int level, std::string &word, std::string_view keyword) {
    if (root_node->is_end_of_node_) {
      std::string construct_word;

      std::cout << "level: " << level << "\n";
      for (int l = 0; l < level; l++) {
        construct_word += word[l];
      }

      result.push_back(keyword.data() + construct_word);
    }

    for (int idx = 0; idx < ALPHABET_LENGTH; idx++) {
      if (root_node->children_[idx] != nullptr) {
        word[level] = static_cast<char>('a' + idx);
        get_words_and_store(root_node->children_[idx], result, level + 1, word, keyword);
      }
    }
  }

  std::vector<std::string> find_all_words(TrieNode *root_node, std::string_view keyword) {
    if (root_node == nullptr) {
      return {};
    }

    std::vector<std::string> words{};
    std::string word{};
    get_words_and_store(root_node, words, 0, word, keyword);

    return words;
  }

  [[maybe_unused]] [[nodiscard]] inline bool delete_node(std::string key) {
    if (key.empty() || root_node_ == nullptr) {
      return false;
    }

    // transform all characters to lowercase
    std::transform(key.begin(), key.end(), key.begin(),
                   [](char c) { return std::tolower(c); });

    TrieNode* current_node = root_node_;

    // start looking at first level
    return delete_recurse(key, current_node, key.size(), 0);
  }

  bool node_has_no_children(TrieNode* current_node) const noexcept {
    for (int idx = 0; idx < ALPHABET_LENGTH; idx++) {
      if (current_node->children_[idx] != nullptr) {
        return false;
      }
    }

    return true;
  }

  // Time Complexity: O(h)
  // h -> length of the key/word being deleted.
  bool delete_recurse(std::string key, TrieNode* current_node, int length,
                      int level) {
    bool deleted_self = false;

    if (current_node == nullptr) {
      return deleted_self;
    }

    // Base case: If we have reached the node which points to the alphabet
    // at the end of the key.
    if (level == length) {
      // If there are no nodes ahead of this node in this path
      // Then we delete this node
      if (node_has_no_children(current_node)) {
        delete current_node;
        current_node = nullptr;
        deleted_self = true;
      }
      // If there are nodes ahead of the current_node in the path
      // Then we cannot delete the current node, we simply unset
      // the node to be the leaf
      else {
        current_node->unmark_as_leaf();
        deleted_self = false;
      }
    } else {
      TrieNode* child_node = current_node->children_[get_index(key[level])];
      bool is_child_deleted =
          delete_recurse(key, child_node, length, level + 1);
      if (is_child_deleted) {
        // Making children pointer also null: since child is already deleted.
        current_node->children_[get_index(key[level])] = nullptr;

        // If current_node is lead node that means current_node is part of
        // another key and therefore we can't delete this node and it's parent
        // nodes
        if (current_node->is_end_of_node_) {
          deleted_self = false;
        }
        // If the child_node is deleted but if current_node has more children
        // then current_node must be part of another key, so we cannot delete
        // the current_node
        else if (!node_has_no_children(current_node)) {
          deleted_self = false;
        }
        // else we delete the current_node
        else {
          current_node = nullptr;
          deleted_self = false;
        }
      } else {
        deleted_self = false;
      }
    }

    return deleted_self;
  }

  TrieNode* get_root_node() { return root_node_; }

 private:
  // contains 26 nullptr nodes at init
  // holds nullptr or another trie_node

  TrieNode* root_node_;
};