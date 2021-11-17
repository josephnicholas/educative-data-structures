#include <catch2/catch.hpp>

#include "trie.hpp"

TEST_CASE("Find with keyword th") {
  auto trie = std::make_unique<Trie>();
  trie->construct_trie(std::vector<std::string>{
      "the", "a", "there", "answer", "any", "by", "bye", "their", "abc"});

  auto words = trie->search_by_prefix("th");

  REQUIRE("the" == words[0]);
  REQUIRE("their" == words[1]);
  REQUIRE("there" == words[2]);
}