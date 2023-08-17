#ifndef DATA_STRUCTURES_CIRCULAR_QUEUE_HPP
#define DATA_STRUCTURES_CIRCULAR_QUEUE_HPP

#include <algorithm>
#include <array>
#include <ranges>

template <typename T, std::size_t MAX_SIZE = 512>
class CircularQueue {
 public:
  CircularQueue() : buffer{std::array<T, MAX_SIZE>{}} {}

  [[nodiscard]] bool put(const T &element) noexcept {
    if (is_full()) {
      return false;
    }

    buffer.at(write_cursor_) = element;
    write_cursor_ = (write_cursor_ + 1) % MAX_SIZE;
    num_of_elements_++;
    return true;
  }

  [[nodiscard]] T get() noexcept {
    if (is_empty()) {
      return T{};
    }

    const auto result = buffer.at(read_cursor_);
    read_cursor_ = (read_cursor_ + 1) % MAX_SIZE;
    num_of_elements_--;

    return result;
  }

  [[nodiscard]] T get_from(uint64_t sequence_id) noexcept {
    if (is_empty()) {
      return T{};
    }

    const auto result = buffer.at(read_cursor_);
    read_cursor_ = (read_cursor_ + 1) % MAX_SIZE;
    num_of_elements_--;

    return result;
  }

  // still put in a circular queue
  void filterBy(std::function<bool(T)> print_callback,
                std::function<bool(T)> predicate) noexcept {
    const auto num_of_elements = elements();
    for (int cursor = 0; cursor < num_of_elements; cursor++) {
      const auto marketTrade = get();
      if (predicate(marketTrade) && !print_callback(marketTrade)) {
        return;
      }
    }
  }

  [[nodiscard]] bool is_empty() const noexcept { return num_of_elements_ == 0; }

  [[nodiscard]] bool is_full() const noexcept {
    return num_of_elements_ == MAX_SIZE;
  }

  [[nodiscard]] size_t elements() const noexcept { return num_of_elements_; }

 private:
  std::array<T, MAX_SIZE> buffer{};
  int read_cursor_{0};
  int write_cursor_{0};
  int num_of_elements_{0};
};
#endif  // DATA_STRUCTURES_CIRCULAR_QUEUE_HPP
