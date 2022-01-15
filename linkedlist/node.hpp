#include <string>
#include <memory>

class Node final {
    public:
        explicit Node() : next_element_(nullptr) {}

        inline void set_node_data(int data) {
            data_ = data;
        }

        [[nodiscard]] inline int get_node_data() const noexcept {
            return data_;
        }

        inline void set_next_node(std::shared_ptr<Node> next_node) {
            next_element_ = std::move(next_node);
        }

        [[nodiscard]] inline std::shared_ptr<Node> get_next_node() const noexcept {
            return next_element_;
        }

    private:
        int data_{};
        std::shared_ptr<Node> next_element_{nullptr};
};