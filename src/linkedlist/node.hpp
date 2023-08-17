#include <memory>
#include <string>

template <typename T>
class Node final {
 public:
  constexpr Node() : next_node_(nullptr) {}
  constexpr explicit Node(T data) : data_(data), next_node_(nullptr) {}

  // TODO: Iterators

  void set_node_data(T data) noexcept {
    data_ = std::move(data);
  }

  void set_next_node(std::shared_ptr<Node> next_node) noexcept {
    next_node_ = std::move(next_node);
  }

  [[nodiscard]] constexpr T get_node_data() const noexcept {
    return data_;
  }

  [[nodiscard]] constexpr std::shared_ptr<Node> get_next_node() const noexcept {
    return next_node_;
  }

 private:
  T data_{};
  std::shared_ptr<Node> next_node_{nullptr};
};