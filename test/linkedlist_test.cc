#include "linkedlist.hpp"

#include "gtest/gtest.h"

struct LinkedListTestShould : public ::testing::Test {
 protected:
  void SetUp() override { linked_list_ = std::make_unique<LinkedList<int>>(); }

  void TearDown() override { linked_list_.reset(); }

  std::unique_ptr<LinkedList<int>> linked_list_{};
};

TEST_F(LinkedListTestShould, InsertAtHead) {
  static constexpr auto num_of_elements{7};
  linked_list_->insert_at_head(1);
  linked_list_->insert_at_head(2);
  linked_list_->insert_at_head(3);
  linked_list_->insert_at_head(4);
  linked_list_->insert_at_head(5);
  linked_list_->insert_at_head(6);
  linked_list_->insert_at_head(7);

  EXPECT_EQ(linked_list_->size(), num_of_elements);
  EXPECT_EQ(linked_list_->get_head()->get_node_data(), 7);
  EXPECT_NE(linked_list_, nullptr);
}

TEST_F(LinkedListTestShould, FindUniqueInLinkedList) {
  const auto list_expected = std::make_unique<LinkedList<int>>();
  list_expected->insert_at_tail(1);
  list_expected->insert_at_tail(2);
  list_expected->insert_at_tail(3);
  list_expected->insert_at_tail(4);

  auto list_one = std::make_unique<LinkedList<int>>();
  list_one->insert_at_tail(1);
  list_one->insert_at_tail(2);
  list_one->insert_at_tail(2);

  auto list_two = std::make_unique<LinkedList<int>>();
  list_two->insert_at_tail(3);
  list_two->insert_at_tail(4);
  list_two->insert_at_tail(4);

  auto result_list = std::make_unique<LinkedList<int>>();
  result_list = result_list->union_list(std::move(list_one), std::move(list_two));

  EXPECT_EQ(list_expected->get_head()->get_node_data(), result_list->get_head()->get_node_data());
}

TEST_F(LinkedListTestShould, FindIntersection) {
  const auto list_expected = std::make_unique<LinkedList<int>>();
  list_expected->insert_at_tail(1);
  list_expected->insert_at_tail(2);
  list_expected->insert_at_tail(3);
  list_expected->insert_at_tail(4);

  auto list_one = std::make_unique<LinkedList<int>>();
  list_one->insert_at_tail(1);
  list_one->insert_at_tail(2);
  list_one->insert_at_tail(2);

  auto list_two = std::make_unique<LinkedList<int>>();
  list_two->insert_at_tail(3);
  list_two->insert_at_tail(4);
  list_two->insert_at_tail(4);

  auto result_list = std::make_unique<LinkedList<int>>();
  result_list = result_list->union_list(std::move(list_one), std::move(list_two));

  EXPECT_EQ(list_expected->get_head()->get_node_data(), result_list->get_head()->get_node_data());
}

TEST_F(LinkedListTestShould, DeleteAtTail) {
    const auto list_expected = std::make_unique<LinkedList<int>>();
    list_expected->insert_at_tail(1);
    list_expected->insert_at_tail(2);
    list_expected->insert_at_tail(3);

    auto list_one = std::make_unique<LinkedList<int>>();
    list_one->insert_at_tail(1);
    list_one->insert_at_tail(2);
    list_one->insert_at_tail(3);
    list_one->insert_at_tail(4);

    auto deleted = list_one->delete_data_at_tail();

    EXPECT_TRUE(deleted);

    auto head_of_expected = list_expected->get_head();
    auto head_of_one = list_one->get_head();
    while (head_of_one->get_next_node() != nullptr && head_of_expected->get_next_node() != nullptr) {
        EXPECT_EQ(head_of_expected->get_node_data(), head_of_one->get_node_data());
        head_of_one = head_of_one->get_next_node();
        head_of_expected = head_of_expected->get_next_node();
    }

    EXPECT_EQ(nullptr, head_of_one->get_next_node());
    EXPECT_EQ(nullptr, head_of_expected->get_next_node());
}
// TODO
/*
int main(int argc, char* argv[]) {
  auto list = std::make_unique<LinkedList>();
  list->insert_at_head(1);
  list->insert_at_head(2);
  list->insert_at_head(3);
  list->insert_at_head(4);
  list->insert_at_head(5);
  list->insert_at_head(6);
  list->insert_at_head(7);
  //    list->has_loop();
  list->print_list();
  //    std::cout << "===============\n";
  //    list->remove_duplicates();
  //    // list->reverse();
  //    list->print_list();
  //
  //    std::cout << "mid = " << list->get_mid() << "\n";
  //
  //
  //    std::cout << "=======Unique=======\n";
  //    LinkedList *list_one = new LinkedList();
  //    list_one->insert_at_tail(1);
  //    list_one->insert_at_tail(2);
  //    list_one->insert_at_tail(2);
  //
  //    LinkedList *list_two = new LinkedList();
  //    list_two->insert_at_tail(3);
  //    list_two->insert_at_tail(4);
  //    list_two->insert_at_tail(4);
  //
  //    LinkedList *result_list = new LinkedList();
  //    result_list->union_list(list_one, list_two)->print_list();
  //
  //    std::cout << "=======Intersection=======\n";
  //    LinkedList *list_one_ = new LinkedList();
  //    list_one_->insert_at_tail(4);
  //    list_one_->insert_at_tail(2);
  //    list_one_->insert_at_tail(6);
  //    list_one_->insert_at_tail(1);
  //
  //    LinkedList *list_two_ = new LinkedList();
  //    list_two_->insert_at_tail(4);
  //    list_two_->insert_at_tail(5);
  //    list_two_->insert_at_tail(6);
  //    list_two_->insert_at_tail(4);
  //    list_two_->insert_at_tail(1);
  //
  //    LinkedList *result_list_ = new LinkedList();
  //    result_list_->interserction(list_one_, list_two_)->print_list();
  //
  //
  //    std::cout << "=======find_nth=======\n";
  //    LinkedList *lists = new LinkedList();
  //    lists->insert_at_tail(15);
  //    lists->insert_at_tail(22);
  //    lists->insert_at_tail(8);
  //    lists->insert_at_tail(7);
  //    lists->insert_at_tail(14);
  //    lists->insert_at_tail(21);
  //    std::cout << lists->find_nth(4) << "\n";
  return 0;
}
*/