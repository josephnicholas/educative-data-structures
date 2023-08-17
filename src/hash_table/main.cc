#include "hash_table.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]) {
  auto hash_table = std::make_unique<HashTable<4>>();

  hash_table->insert("London",2);
  hash_table->insert("London",10);
  hash_table->insert("New York",15);
  hash_table->insert("Tokyo",7);
  hash_table->insert("Bangkok",2);

//  hash_table->delete_key("London");
//
  hash_table->display();
//
//  std::cout << "\n";
//
  hash_table->resize();
  hash_table->insert("Beijing",6);
  hash_table->insert("Islamabad",9);
  hash_table->insert("New Delhi",17);
  hash_table->insert("Moscow",12);
  hash_table->insert("Amsterdam",5);
  hash_table->insert("Paris",13);
  hash_table->display();
//
//  std::cout << hash_table->search("Amsterdam") << "\n";
//
  hash_table->delete_key("Beijing");
//  hash_table->display();
  return 0;
}