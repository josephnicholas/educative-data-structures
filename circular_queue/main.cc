#include <iostream>
#include <memory>

#include "circular_queue.hpp"

struct MarketTrade {
  std::string msg{};
};

using MarketTradeWithSequenceType = std::pair<MarketTrade, uint64_t>;

int main() {
  std::cout << "Hello, Circular Queue!\n";

  const auto circular_buffer = std::make_unique<CircularQueue<MarketTradeWithSequenceType>>();
  std::ignore = circular_buffer->put({MarketTrade{.msg = "Market Trade 1"}, 1});
  std::ignore = circular_buffer->put({MarketTrade{.msg = "Market Trade 2"}, 2});
  std::ignore = circular_buffer->put({MarketTrade{.msg = "Market Trade 3"}, 3});
  std::ignore = circular_buffer->put({MarketTrade{.msg = "Market Trade 4"}, 4});

  auto print_callback = [](const MarketTradeWithSequenceType &message) {
    std::cout << message.first.msg << "\n";
    return true;
  };

  auto predicate = [](const MarketTradeWithSequenceType &marketTrade) {
    return marketTrade.second >= 2;
  };

  circular_buffer->filterBy(print_callback, predicate);
//  const auto num_of_elements = circular_buffer->elements();
//  for (int cursor = 0; cursor < num_of_elements; cursor++) {
//    const auto marketTrade = circular_buffer->get();
//    std::cout << marketTrade.second << " " << marketTrade.first.msg << "\n";
//  }
  return 0;
}