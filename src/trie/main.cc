#include "trie.hpp"
#include <iostream>
#include <string_view>
#include <memory>

[[maybe_unused]] auto total_words(TrieNode *root_node) {
  if (root_node == nullptr) {
    return 0;
  }

  TrieNode *current_node = root_node;
  int word_count = 0;

  if (current_node->is_end_of_node_) {
    word_count++;
  }

  for (int idx = 0; idx < ALPHABET_LENGTH; idx++) {
    if (current_node->children_[idx] != nullptr) {
      word_count += total_words(current_node->children_[idx]);
    }
  }

  return word_count;
}

[[maybe_unused]] auto print_all(std::vector<std::string> const &words) {
  for (const auto &word : words) {
    std::cout << word << "\n";
  }
}

int main() {
  auto trie = std::make_unique<Trie>();

  trie->construct_trie(std::vector<std::string>{
      "the", "a", "there", "answer", "any", "by", "bye", "their", "abc"});

  std::cout << "\n======================================\n";
  std::string_view prefix = "thei";
  std::string extracted_prefix;
  std::vector<std::vector<std::string>> result{};

  for (const auto &ch : prefix) {
    extracted_prefix += ch;
    if (extracted_prefix.size() > 1) {
      // this means we already have atleast 2 letter prefix.
      // search by keyword
      std::cout << "searching for: " << extracted_prefix << "\n";
      result.push_back(trie->search_by_prefix(extracted_prefix));
    }
  }

  for (const auto &v : result) {
    std::cout << "{\n";
    for (const auto &n : v) {
      std::cout << "\t\t" <<n << ",\n";
    }
    std::cout << "}\n\n";
  }

  return 0;
}