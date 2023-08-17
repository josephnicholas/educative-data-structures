#include "stack.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  Stack<int> stk{};
  assert(stk.push(0));
  assert(stk.push(1));
  assert(stk.push(2));
  assert(stk.push(3));
  assert(stk.push(4));

  std::cout << "Pop top of stack: " << stk.pop() << "\n";
  std::cout << "Pop top of stack: " << stk.pop() << "\n";
  std::cout << "Top of stack: " << stk.top() << "\n";
  return 0;
}