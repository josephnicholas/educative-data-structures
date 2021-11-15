#ifndef DATA_STRUCTURES_STACK_HPP
#define DATA_STRUCTURES_STACK_HPP

#include <array>
#include <cassert>
#include <iostream>

template <int T = 5>
class Stack final {
 public:
  explicit Stack()
      : capacity{T}, stack_array{std::array<int, T>{}}, num_of_elements{0} {}

  [[maybe_unused]] [[nodiscard]] inline bool is_empty() const noexcept {
    return num_of_elements == 0;
  }

  [[maybe_unused]] [[nodiscard]] inline int top() const noexcept {
    return num_of_elements == 0 ? -1 : stack_array[num_of_elements - 1];
  }

  [[maybe_unused]] [[nodiscard]] inline int size() const noexcept {
    return num_of_elements;
  }

  [[maybe_unused]] [[nodiscard]] inline bool push(int value) {
    if (num_of_elements < capacity) {
      stack_array[num_of_elements] = value;
      num_of_elements++;
      return true;
    }

    std::cerr << "Stack is full!\n";
    return false;
  }

  [[maybe_unused]] [[nodiscard]] inline int pop() {
    if (!is_empty()) {
      num_of_elements--;
      return stack_array[num_of_elements];
    }

    std::cerr << "Stack is empty!\n";
    return -1;
  }

 private:
  std::array<int, T> stack_array{};
  int capacity;
  int num_of_elements;
};
#endif  // DATA_STRUCTURES_STACK_HPP
