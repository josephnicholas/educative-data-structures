#include <string>
#include <memory>

template<typename T>
class Node final {
    public:
        explicit Node() : next_node_(nullptr) {}
        explicit Node(T data) : data_(data), next_node_(nullptr) {}

        inline void set_node_data(T data) {
            data_ = data;
        }

        [[nodiscard]] inline auto get_node_data() const noexcept -> int {
            return data_;
        }

        inline void set_next_node(std::shared_ptr<Node> next_node) noexcept {
            next_node_ = std::move(next_node);
        }

        [[nodiscard]] inline auto get_next_node() const noexcept -> std::shared_ptr<Node> {
            return next_node_;
        }

    private:
        T data_{};
        std::shared_ptr<Node> next_node_{nullptr};
};