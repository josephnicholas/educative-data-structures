#ifndef DATA_STRUCTURES_QUEUE_HPP
#define DATA_STRUCTURES_QUEUE_HPP

#include <array>
#include <iostream>

template <int T = 5>
class Queue final {
  // enqueue - inserts elements at the end
  // dequeue - removes an element from the start of queue
  // front - returns first element of the queue
  // empty - checks is queue is empty
 public:
  Queue()
      : queue_array_{std::array<int, T>{}},
        capacity_{T},
        num_of_elements_{0},
        front_{0},
        back_{-1} {}

  [[maybe_unused]] [[nodiscard]] inline auto empty() const noexcept {
    return num_of_elements_ == 0;
  }

  [[maybe_unused]] [[nodiscard]] inline auto front() const noexcept {
    if (empty()) {
      return -1;
    }
    return queue_array_.at(front_);
  }

  [[maybe_unused]] [[nodiscard]] inline auto back() const noexcept {
    if (empty()) {
      return -1;
    }
    return queue_array_.at(num_of_elements_ - back_);
  }

  [[maybe_unused]] [[nodiscard]] inline auto size() const noexcept {
    return num_of_elements_;
  }

  [[maybe_unused]] inline void enqueue(int value) {
    if (num_of_elements_ == capacity_) {
      std::cerr << "Queue is full\n";
      return;
    }

    if (back_ == capacity_ - 1) {
      // if back reaches end of array
      // reset back
      back_ = -1;
    }

    queue_array_.at(++back_) = value;
    num_of_elements_++;
  }

  [[maybe_unused]] [[nodiscard]] inline auto dequeue() {
    if (empty()) {
      std::cerr << "Queue is empty\n";
      return -1;
    }

    const auto value = queue_array_.at(front_++);

    if (front_ == capacity_) {
      // if front reaches end of queue
      // reset front
      front_ = 0;
    }

    num_of_elements_--;
    return value;
  }

 private:
  std::array<int, T> queue_array_{};
  int capacity_{};
  int num_of_elements_{};
  int front_{};
  int back_{};
};
#endif  // DATA_STRUCTURES_QUEUE_HPP
