#ifndef DATA_STRUCTURES_QUEUE_HPP
#define DATA_STRUCTURES_QUEUE_HPP

#include <array>
#include <iostream>

// TODO make doubly linked list queue implementation
// TODO finish the doubly linked list first

template <typename T, size_t Size = 5>
class Queue final {
  // enqueue - inserts elements at the end
  // dequeue - removes an element from the start of queue
  // front - returns first element of the queue
  // empty - checks is queue is empty
 public:
  constexpr Queue() noexcept : capacity_{Size} {
    queue_array_.reserve(Size);
  }

  [[nodiscard]] constexpr auto empty() const noexcept -> bool {
    return num_of_elements_ == 0;
  }

  [[nodiscard]] constexpr auto front() const noexcept -> T {
    if (empty()) {
      return -1;
    }

    return queue_array_.at(front_);
  }

  [[nodiscard]] constexpr auto back() const noexcept -> T {
    if (empty()) {
      return -1;
    }

    return queue_array_.at(queue_array_.size() - 1);
  }

  [[nodiscard]] constexpr auto size() const noexcept -> size_t {
    return queue_array_.size();
  }

  [[maybe_unused]] inline void enqueue(T value) {
    if (num_of_elements_ == capacity_) {
      std::cerr << "Queue is full\n";
      return;
    }

    queue_array_.push_back(value);
    num_of_elements_++;
  }

  [[maybe_unused]] [[nodiscard]] inline auto dequeue() {
    if (empty()) {
      std::cerr << "Queue is empty\n";
      return -1;
    }

    const auto value = queue_array_.at(front_);
    queue_array_.erase(queue_array_.begin() + front_);

    return value;
  }

 private:
  std::vector<T> queue_array_{};
  size_t capacity_{};
  size_t num_of_elements_{};
  size_t front_{};
  size_t back_{};
};
#endif  // DATA_STRUCTURES_QUEUE_HPP
