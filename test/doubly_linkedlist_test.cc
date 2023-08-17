#include "doubly_linkedlist.hpp"

#include "gtest/gtest.h"

struct DoublyLinkedListTestShould : public ::testing::Test {
 protected:
  void SetUp() override { linked_list_ = std::make_unique<DoublyLinkedList<int>>(); }

  void TearDown() override { linked_list_.reset(); }

  std::unique_ptr<DoublyLinkedList<int>> linked_list_{};
};

TEST_F(DoublyLinkedListTestShould, InsertAtHead) {
  static constexpr unsigned int num_of_elements{7};
  linked_list_->insert_at_head(1);
  linked_list_->insert_at_head(2);
  linked_list_->insert_at_head(3);
  linked_list_->insert_at_head(4);
  linked_list_->insert_at_head(5);
  linked_list_->insert_at_head(6);
  linked_list_->insert_at_head(7);

  EXPECT_EQ(linked_list_->size(), num_of_elements);
  EXPECT_EQ(linked_list_->get_head()->get_node_data(), 7);
  EXPECT_EQ(linked_list_->get_head()->get_next_node()->get_node_data(), 6);

  const auto node_five = linked_list_->get_head()->get_next_node()->get_next_node();
  EXPECT_EQ(node_five->get_node_data(), 5);
  EXPECT_EQ(node_five->get_next_node()->get_node_data(), 4);
  const auto node_five_ptr = node_five->get_prev_node().lock();
  EXPECT_EQ(node_five_ptr->get_node_data(), 6);
  EXPECT_NE(linked_list_, nullptr);
}

TEST_F(DoublyLinkedListTestShould, InsertAtTail) {
  static constexpr unsigned int num_of_elements{7};
  linked_list_->insert_at_tail(1);
  linked_list_->insert_at_tail(2);
  linked_list_->insert_at_tail(3);
  linked_list_->insert_at_tail(4);
  linked_list_->insert_at_tail(5);
  linked_list_->insert_at_tail(6);
  linked_list_->insert_at_tail(7);

  EXPECT_EQ(linked_list_->size(), num_of_elements);
  EXPECT_EQ(linked_list_->get_head()->get_node_data(), 1);

  const auto mid_node = linked_list_->get_head()->get_next_node();
  const auto mid_node_ptr = mid_node->get_prev_node().lock();
  EXPECT_EQ(mid_node_ptr->get_node_data(), 1);
  EXPECT_EQ(mid_node->get_node_data(), 2);
  EXPECT_EQ(mid_node->get_next_node()->get_node_data(), 3);
  EXPECT_NE(linked_list_, nullptr);
}

TEST_F(DoublyLinkedListTestShould, DeleteDataAtLinkedList) {
    static constexpr unsigned int num_of_elements{7};
    linked_list_->insert_at_tail(1);
    linked_list_->insert_at_tail(2);
    linked_list_->insert_at_tail(3);
    linked_list_->insert_at_tail(4);
    linked_list_->insert_at_tail(5);
    linked_list_->insert_at_tail(6);
    linked_list_->insert_at_tail(7);

    EXPECT_EQ(linked_list_->size(), num_of_elements);
    EXPECT_EQ(linked_list_->get_head()->get_node_data(), 1);

    EXPECT_TRUE(linked_list_->delete_data(5));
}

TEST_F(DoublyLinkedListTestShould, FindAndRemoveFiveInTheList) {
    linked_list_->insert_at_tail(1);
    linked_list_->insert_at_tail(2);
    linked_list_->insert_at_tail(3);
    linked_list_->insert_at_tail(4);
    linked_list_->insert_at_tail(5);
    linked_list_->insert_at_tail(6);
    linked_list_->insert_at_tail(7);

    EXPECT_TRUE(linked_list_->search(5));
    EXPECT_TRUE(linked_list_->delete_data(5));
    EXPECT_FALSE(linked_list_->delete_data(5));
    EXPECT_FALSE(linked_list_->delete_data(5));
}