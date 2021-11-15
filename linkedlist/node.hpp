#include <string>

class Node final {
    public:
        explicit Node() : next_element_(nullptr) {}

        inline void set_node_data(int data) {
            data_ = data;
        }

        [[nodiscard]] inline int get_node_data() {
            return data_;
        }

        inline void set_next_node(Node* next_node) {
            next_element_ = next_node;
        }

        [[nodiscard]] inline Node* get_next_node() {
            return next_element_;
        }

    private:
        int data_{};
        Node* next_element_{nullptr};
};