#include <memory>
#include <vector>
#include <string>

#include "queue.hpp"

template <int N>
std::vector<std::string> find_binary() {
  std::vector<std::string> result{};
  auto queue = std::make_unique<Queue<N + 1>>();

  // start with 1
  queue->enqueue(1);

  std::string temp_str1{};
  std::string temp_str2{};
  for (int i = 0; i < N; i++) {
    result.push_back(std::to_string(queue->dequeue()));

    // 10
    temp_str1 = result.at(i) + "0";

    // 11
    temp_str2 = result.at(i) + "1";

    // enqueue(10)
    queue->enqueue(std::stoi(temp_str1));

    // enqueue(11)
    queue->enqueue(std::stoi(temp_str2));
  }

  return result;
}

int main(int argc, char* argv[]) {
  for (const auto &binary : find_binary<10>()) {
    std::cout << binary << ",\n";
  }
  return 0;
}