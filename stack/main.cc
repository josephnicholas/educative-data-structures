#include "stack.hpp"
#include <memory>

int main(int argc, char* argv[]) {
  auto stack = std::make_unique<Stack<10>>();
  assert(stack->push(0));
  assert(stack->push(1));
  assert(stack->push(2));
  assert(stack->push(3));
  assert(stack->push(4)); // <---- top of stack

  std::cout << "Pop top of stack: " << stack->pop() << "\n";
  std::cout << "Pop top of stack: " << stack->pop() << "\n";
  return 0;
}