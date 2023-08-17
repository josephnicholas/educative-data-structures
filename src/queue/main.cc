#include <memory>
#include <string>
#include <vector>

#include "queue.hpp"

// template <size_t N>
// std::vector<std::string> find_binary() {
//   std::vector<std::string> result{};
//   auto queue = std::make_unique<Queue<int, N + 1>>();
//
//   // start with 1
//   queue->enqueue(1);
//
//   std::string temp_str1{};
//   std::string temp_str2{};
//   for (size_t i = 0; i < N; i++) {
//     result.push_back(std::to_string(queue->dequeue()));
//
//     // 10
//     temp_str1 = result.at(i) + "0";
//
//     // 11
//     temp_str2 = result.at(i) + "1";
//
//     // enqueue(10)
//     queue->enqueue(std::stoi(temp_str1));
//
//     // enqueue(11)
//     queue->enqueue(std::stoi(temp_str2));
//   }
//
//   return result;
// }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  Queue<int, 5> queue{};
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.enqueue(4);
  queue.enqueue(5);

  std::cout << "Dequeue: " << queue.dequeue() << "\n";
  std::cout << "Front: " << queue.front() << "\n";
  std::cout << "Back: " << queue.back() << "\n";

  return 0;
}