#ifndef DATA_STRUCTURES_ALGORITHMS_PATTERNS_HPP
#define DATA_STRUCTURES_ALGORITHMS_PATTERNS_HPP

#include <vector>

class AlgorithmsPatterns {
 public:
  std::vector<int> bubbleSort(std::vector<int> array, int offset = 0) {
    bool did_swap = false;
    for (int idx = 0; idx < array.size() - 1 - offset; idx++) {
      if (array[idx] > array[idx + 1]) {
        std::swap(array[idx], array[idx + 1]);
        did_swap = true;
      }
    }

    if (did_swap) {
      return bubbleSort(array, offset + 1);
    }

    return array;
  }

  std::vector<int> right_shift(std::vector<int> array, int offset = 0) {
    // take last element
    // to avoid it from overlapping
    // use it as the first element
    const auto last_element = array[array.size() - 1];
    for (auto idx = array.size() - 2; idx >= 0; idx--) {
      array[idx + 1] = array[idx];
    }

    array[0] = last_element;

    return array;
  }
};

#endif  // DATA_STRUCTURES_ALGORITHMS_PATTERNS_HPP
