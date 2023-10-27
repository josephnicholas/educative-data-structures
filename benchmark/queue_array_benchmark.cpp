#include <benchmark/benchmark.h>
#include <memory>
#include <queue>

#include "queue.hpp"

constexpr auto NUMBER_OF_INTS{100'000'000};
static void BM_EnqueueIntsInQueueArray(benchmark::State& state) {
  const auto q = std::make_unique<Queue<int, NUMBER_OF_INTS>>();
  for ([[maybe_unused]] auto stt : state) {
    for (int i = 1; i <= NUMBER_OF_INTS; ++i) {
      q->enqueue(i);
    }
  }
}
BENCHMARK(BM_EnqueueIntsInQueueArray);

static void BM_EnqueueIntsInStdQueue(benchmark::State& state) {
  const auto q = std::make_unique<std::queue<int>>();
  for ([[maybe_unused]] auto stt : state) {
    for (int i = 1; i <= NUMBER_OF_INTS; ++i) {
      q->push(i);
    }
  }
}
BENCHMARK(BM_EnqueueIntsInStdQueue);

static void BM_DequeueQueueArray(benchmark::State& state) {
  const auto queue = std::make_unique<Queue<int, NUMBER_OF_INTS>>();
  for (int i = 1; i <= NUMBER_OF_INTS; ++i) {
    queue->enqueue(i);
  }

  for ([[maybe_unused]] auto stt : state) {
    std::ignore = queue->dequeue();
  }
}
BENCHMARK(BM_DequeueQueueArray);

BENCHMARK_MAIN();