#include "linkedlist.hpp"

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
