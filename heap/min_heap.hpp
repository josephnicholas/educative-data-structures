#ifndef DATA_STRUCTURES_MIN_HEAP_HPP
#define DATA_STRUCTURES_MIN_HEAP_HPP

#include <vector>
#include <iostream>

template <typename T>
class MinHeap final {
 public:

  [[nodiscard]] inline int parent(int idx) const noexcept {
    return (idx - 1) / 2;
  }

  [[nodiscard]] inline int left_child(int kdx) const noexcept {
    return (2 * kdx) + 1;
  }

  [[nodiscard]] inline int right_child(int kdx) const noexcept {
    return (2 * kdx) + 2;
  }

  MinHeap() {
    heap.resize(0);
  };

  [[nodiscard]] inline int size() const noexcept { return heap.size(); }

  [[nodiscard]] inline T get_min() const {
    if (heap.empty()) {
      return -1;
    }

    return heap.at(0);
  }

  // O(log n)
  // inserts key at the end of the list
  // since we are traversing/swapping max "n" nodes
  inline void insert(const T &key) {
    heap.push_back(key);

    // store the index of the last value of the vector
    int idx = size() - 1;

    // restore heap property
    percolate_up(idx);
  }

  // O(log n)
  // since we are traversing/swapping max "n" nodes
  inline void remove_min() {
    if (size() == 1) {
      heap.pop_back();
    } else if (size() > 1) {
      std::swap(heap.at(0), heap.at(size() - 1));
      heap.pop_back();

      // restore max_heap property
      min_heapify(0);
    }
  }

  // O(n)
  inline void build_heap(T list_to_heap[], int n) {
    std::copy(&list_to_heap[0], &list_to_heap[n], std::back_inserter(heap));

    // iterate through every key and perform max_heapify
    for (int idx = (n - 1) / 2; idx >= 0; idx--) {
      min_heapify(idx);
    }
  }

  inline void print() const noexcept {
    for (auto const& n : heap) {
      std::cout << n << ", ";
    }
    std::cout << "\n";
  }

 private:
  std::vector<T> heap{};
  void percolate_up(int idx) {
    if (idx <= 0) {
      return;
    }
    if (heap.at(parent(idx)) > heap.at(idx)) {
      std::swap(heap.at(parent(idx)), heap.at(idx));
      percolate_up(parent(idx));
    }
  }

  // O(logn)
  // makes the most of height - idx comparisons per level
  void min_heapify(int idx) {
    int left_child_idx = left_child(idx);
    int right_child_idx = right_child(idx);
    int min_at_idx = idx;

    // check each child separately
    if (left_child_idx < size() && heap.at(left_child_idx) < heap.at(min_at_idx)) {
      min_at_idx = left_child_idx;
    }

    if (right_child_idx < size() && heap.at(right_child_idx) < heap.at(min_at_idx)) {
      min_at_idx = right_child_idx;
    }

    if(min_at_idx != idx) {
      std::swap(heap.at(idx), heap.at(min_at_idx));
      min_heapify(min_at_idx);
    }
  }
};
#endif  // DATA_STRUCTURES_MIN_HEAP_HPP
