#ifndef DATA_STRUCTURES_STACK_HPP
#define DATA_STRUCTURES_STACK_HPP

#include <array>
#include <cassert>
#include <iostream>

static constexpr auto DEFAULT_SIZE{5};
template <typename T, size_t Size = DEFAULT_SIZE>
class Stack final {
 public:
  constexpr Stack() noexcept
      : stack_array_{std::array<T, Size>{}}, capacity_{Size} {}

  [[nodiscard]] constexpr auto is_empty() const noexcept -> bool {
    return num_of_elements_ == 0;
  }

  [[nodiscard]] constexpr auto top() const noexcept -> T {
    return num_of_elements_ == 0 ? -1 : stack_array_[num_of_elements_ - 1];
  }

  [[nodiscard]] consteval auto size() const noexcept -> size_t {
    return num_of_elements_;
  }

  [[nodiscard]] constexpr auto push(int value) noexcept -> bool {
    if (num_of_elements_ < capacity_) {
      stack_array_[num_of_elements_] = value;
      num_of_elements_++;
      return true;
    }

    std::cerr << "Stack is full!\n";
    return false;
  }

  [[nodiscard]] constexpr auto pop() noexcept -> T {
    if (!is_empty()) {
      return stack_array_[--num_of_elements_];
    }

    std::cerr << "Stack is empty!\n";
    return -1;
  }

 private:
  std::array<T, Size> stack_array_{};
  decltype(Size) capacity_;
  decltype(Size) num_of_elements_{0};
};
#endif  // DATA_STRUCTURES_STACK_HPP
