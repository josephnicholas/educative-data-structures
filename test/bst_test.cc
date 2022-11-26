#include "binary_search_tree.hpp"

#include "gtest/gtest.h"

struct BinarySearchTreeShould : public ::testing::Test {
 protected:
  void SetUp() override {
    tree_sut = std::make_unique<BinarySearchTree<int>>(2);
    tree_sut->insert_node(1);
    tree_sut->insert_node(3);
  }

  void TearDown() override {

  }

  std::unique_ptr<BinarySearchTree<int>> tree_sut{};
};

TEST_F(BinarySearchTreeShould, InsertValuesInTheTree) {
  const auto tree = std::make_unique<BinarySearchTree<int>>(2);
  tree->insert_node(1);
  tree->insert_node(3);
  EXPECT_TRUE(*tree_sut == tree.get());
}

TEST_F(BinarySearchTreeShould, InsertDuplicateValuesInTheTree) {
  const auto tree = std::make_unique<BinarySearchTree<int>>(2);
  tree->insert_node(1);
  tree->insert_node(1);
  tree->insert_node(3);
  tree->insert_node(4);

  Node<int>* found_node = tree->search_recursive(tree->get_root(), 1);
  EXPECT_EQ(2, found_node->count_);
}

TEST_F(BinarySearchTreeShould, DeleteNodeWith2Children) {
  const auto tree = std::make_unique<BinarySearchTree<int>>(6);
  tree->insert_node(4);
  tree->insert_node(9);
  tree->insert_node(2);
  tree->insert_node(5);
  tree->insert_node(8);
  tree->insert_node(12);
  tree->insert_node(10);
  tree->insert_node(14);

  EXPECT_EQ(BinarySearchTree<int>::search_recursive(tree->get_root(), 9)->value_, 9);
  EXPECT_TRUE(tree->delete_node(tree->get_root(), 9));
  EXPECT_EQ(BinarySearchTree<int>::search_recursive(tree->get_root(), 9), nullptr);
}

TEST_F(BinarySearchTreeShould, DeleteNodeWith2ChildrenWithDuplicate) {
  const auto tree = std::make_unique<BinarySearchTree<int>>(6);
  tree->insert_node(4);
  tree->insert_node(4);
  tree->insert_node(9);
  tree->insert_node(2);
  tree->insert_node(5);
  tree->insert_node(8);
  tree->insert_node(12);
  tree->insert_node(10);
  tree->insert_node(14);

  EXPECT_EQ(BinarySearchTree<int>::search_recursive(tree->get_root(), 4)->value_, 4);
  EXPECT_TRUE(tree->delete_node(tree->get_root(), 4));
  EXPECT_EQ(BinarySearchTree<int>::search_recursive(tree->get_root(), 4)->value_, 4);
  EXPECT_TRUE(tree->delete_node(tree->get_root(), 4));
  EXPECT_EQ(BinarySearchTree<int>::search_recursive(tree->get_root(), 4), nullptr);
}

TEST_F(BinarySearchTreeShould, FlattenInOrder) {
  const auto tree = std::make_unique<BinarySearchTree<int>>(6);
  tree->insert_node(4);
  tree->insert_node(9);
  tree->insert_node(2);
  tree->insert_node(5);
  tree->insert_node(8);
  tree->insert_node(12);

  const std::vector<int> expected{2, 4, 5, 6, 8, 9, 12};
  std::vector<int> flat{};
  tree->in_order_traversal(tree->get_root(), flat);

  EXPECT_EQ(expected, flat);
}

TEST_F(BinarySearchTreeShould, GetHeight) {
  const auto tree = std::make_unique<BinarySearchTree<int>>(6);
  tree->insert_node(4);
  tree->insert_node(9);
  tree->insert_node(2);
  tree->insert_node(5);
  tree->insert_node(8);
  tree->insert_node(12);

  constexpr auto height{2};
  EXPECT_EQ(height, tree->height(tree->get_root()));
}

TEST_F(BinarySearchTreeShould, GetBalanceFactor) {
  const auto tree = std::make_unique<BinarySearchTree<int>>(6);
  tree->insert_node(4);
  tree->insert_node(9);
  tree->insert_node(2);
  tree->insert_node(5);
  tree->insert_node(8);
  tree->insert_node(12);

  constexpr auto balance_factor{0};
  EXPECT_EQ(balance_factor, tree->balance_factor());
}

TEST_F(BinarySearchTreeShould, UnbalancedTreeBalanceFactor) {
  const auto tree = std::make_unique<BinarySearchTree<int>>(6);
  tree->insert_node(4);
  tree->insert_node(9);
  tree->insert_node(2);
  tree->insert_node(5);
  tree->insert_node(8);
  tree->insert_node(12);
  tree->insert_node(13);
  tree->insert_node(14);
  tree->insert_node(15);

  constexpr auto balance_factor{0};
  EXPECT_NE(balance_factor, tree->balance_factor());
}
