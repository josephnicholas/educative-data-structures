#include <memory>

#include <queue>

#include "max_heap.hpp"
#include "min_heap.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  MaxHeap<int> max_heap{};
  max_heap.insert(2);
  max_heap.insert(8);
  max_heap.insert(15);
  max_heap.insert(5);
  max_heap.insert(1);
  max_heap.insert(20);

  std::cout << max_heap.get_max() << "\n";
//  max_heap->remove_max();
//  std::cout << max_heap->get_max() << "\n";
//
//  const auto max_heap_2 = std::make_unique<MaxHeap<int>>();
//  max_heap_2->insert(3);
//  int nums[] = {2,3,1,2,4,5,5,6};
//  max_heap_2->build_heap(nums, 8);
//  max_heap_2->print();
//
//  std::cout << max_heap_2->get_max() << "\n";
//
//  std::cout << "===min-heap_===\n";
//  auto min_heap = std::make_unique<MinHeap<int>>();
//  min_heap->insert(2);
//  min_heap->insert(8);
//  min_heap->insert(15);
//  min_heap->insert(5);
//  min_heap->insert(1);
//  min_heap->insert(20);
//
//  std::cout << min_heap->get_min() << "\n";
//  min_heap->remove_min();
//  std::cout << min_heap->get_min() << "\n";
//
//  auto min_heap_2 = std::make_unique<MinHeap<int>>();
//  int input[] = {9,4,7,1,-2,6,5};
//  min_heap_2->build_heap(input, 7);
//  min_heap_2->print();
//
//  std::priority_queue<int, std::vector<int>, std::greater<>> min_pq_heap{};
//
//  min_pq_heap.push(2);
//  min_pq_heap.push(8);
//  min_pq_heap.push(15);
//  min_pq_heap.push(5);
//  min_pq_heap.push(1);
//  min_pq_heap.push(20);
//
//  while (!min_pq_heap.empty()) {
//    std::cout << min_pq_heap.top() << "\n";
//    min_pq_heap.pop();
//  }
  return 0;
}