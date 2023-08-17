#ifndef DATA_STRUCTURES_MAX_HEAP_HPP
#define DATA_STRUCTURES_MAX_HEAP_HPP

#include <iostream>
#include <array>

template <typename T, size_t Size = 6>
class MaxHeap final {
 public:
  constexpr MaxHeap() noexcept { heap_.resize(Size); };

  [[nodiscard]] constexpr auto parent(size_t idx) const noexcept -> size_t {
    return (idx - 1) / 2;
  }

  [[nodiscard]] constexpr auto left_child(size_t kdx) const noexcept -> size_t {
    return (2 * kdx) + 1;
  }

  [[nodiscard]] constexpr auto right_child(size_t kdx) const noexcept -> size_t {
    return (2 * kdx) + 2;
  }

  [[nodiscard]] inline auto size() const noexcept -> size_t {
    return Size;
  }

  [[nodiscard]] inline T get_max() const {
    if (heap_.empty()) {
      return -1;
    }

    return heap_.at(0);
  }

  // O(log n)
  // inserts key at the end of the list
  // since we are traversing/swapping max "n" nodes
  inline void insert(const T& key) {
    heap_.push_back(key);

    // store the index of the last value of the vector
    const auto idx = size() - 1;

    // restore heap_ property
    percolate_up(idx);
  }

  // O(log n)
  // since we are traversing/swapping max "n" nodes
  inline void remove_max() {
    if (size() == 1) {
      heap_.pop_back();
    } else if (size() > 1) {
      std::swap(heap_.at(0), heap_.at(size() - 1));
      heap_.pop_back();

      // restore max_heap property
      max_heapify(0);
    }
  }

  // O(n)
  inline void build_heap(T list_to_heap[], int n) {
    std::copy(&list_to_heap[0], &list_to_heap[n], std::back_inserter(heap_));

    // iterate through every key and perform max_heapify
    for (int idx = (n - 1) / 2; idx >= 0; idx--) {
      max_heapify(idx);
    }
  }

  inline void print() const noexcept {
    for (auto const& n : heap_) {
      std::cout << n << ", ";
    }
    std::cout << "\n";
  }

 private:
  void percolate_up(size_t idx) {
    if (idx == 0) {
      return;
    }

    if (heap_.at(parent(idx)) < heap_.at(idx)) {
      std::swap(heap_.at(parent(idx)), heap_.at(idx));
      percolate_up(parent(idx));
    }
  }

  // O(logn)
  // makes the most of height - idx comparisons per level
  void max_heapify(int idx) {
    int left_child_idx = left_child(idx);
    int right_child_idx = right_child(idx);
    int max_at_idx = idx;

    // check each child separately
    if (left_child_idx < size() &&
        heap_.at(left_child_idx) > heap_.at(max_at_idx)) {
      max_at_idx = left_child_idx;
    }

    if (right_child_idx < size() &&
        heap_.at(right_child_idx) > heap_.at(max_at_idx)) {
      max_at_idx = right_child_idx;
    }

    if (max_at_idx != idx) {
      std::swap(heap_.at(idx), heap_.at(max_at_idx));
      max_heapify(max_at_idx);
    }
  }

 private:
  std::vector<T> heap_;
};

#endif  // DATA_STRUCTURES_MAX_HEAP_HPP
