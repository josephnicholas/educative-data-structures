#include "trie.hpp"
#include <exception>
#include <iostream>

int total_words(TrieNode *root_node) {
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


void print_all(std::vector<std::string> const &words) {
  for (const auto &word : words) {
    std::cout << word << "\n";
  }
}

int main() {
  Trie *trie = new Trie();

  trie->construct_trie(std::vector<std::string>{
      "the", "a", "there", "answer", "any", "by", "bye", "their", "abc"});
//  std::cout << "=========find_all_words=========\n";
//  print_all(find_all_words(trie->get_root_node()));
//
//  std::cout << "=========total_words=========\n";
//  std::cout << total_words(trie->get_root_node()) << "\n";
//  std::cout << trie->search_node("the") << "\n";
  for(const auto &word : trie->search_by_prefix("te")) {
    std::cout << word << ",";
  }

  for(const auto &word : trie->search_by_prefix("an")) {
    std::cout << word << ",";
  }
  // std::cout << trie->search_node("the") << "\n";
  // std::cout << trie->search_node("th") << "\n";

  // std::cout << trie->delete_node("the") << "\n";
  // std::cout << trie->search_node("the") << "\n";
  return 0;
}