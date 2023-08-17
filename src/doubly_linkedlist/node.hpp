#ifndef DATA_STRUCTURES_NODE_HPP
#define DATA_STRUCTURES_NODE_HPP

#include <memory>

template <typename T>
class Node final {
 public:
  constexpr explicit Node(T data) : data_{data} {}

  // TODO: Iterators

  void set_node_data(T data) noexcept {
    data_ = std::move(data);
  }

  void set_next_node(std::shared_ptr<Node<T>> next_node) noexcept {
    next_node_ = next_node;
  }

  void set_prev_node(std::weak_ptr<Node<T>> previous_node) noexcept {
    previous_node_ = previous_node;
  }

  [[nodiscard]] constexpr T get_node_data() const noexcept {
    return data_;
  }

  [[nodiscard]] constexpr std::shared_ptr<Node<T>> get_next_node() const noexcept {
    return next_node_;
  }

  [[nodiscard]] constexpr std::weak_ptr<Node<T>> get_prev_node() const noexcept {
    return previous_node_;
  }

 private:
  T data_{};
  std::shared_ptr<Node<T>> next_node_;
  std::weak_ptr<Node<T>> previous_node_;
};

#endif  // DATA_STRUCTURES_NODE_HPP
