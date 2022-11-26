#include <cstddef>
#include <iostream>
#include <cmath>
#include <string>

#include "node.hpp"

template<typename T>
class LinkedList final {
    public:
        LinkedList() = default;
        ~LinkedList() = default;

        [[maybe_unused]] inline void insert_at(T data, int n) {}

        inline void insert_at_tail(T data) {
            // traverse the list until it is a nullptr(tail)
            if (is_empty()) {
                insert_at_head(data);
            } else {
                auto new_node = std::make_shared<Node<T>>();
                std::shared_ptr<Node<T>> tail_node = head_;

                while(tail_node->get_next_node() != nullptr) {
                    tail_node = tail_node->get_next_node();
                }

                new_node->set_node_data(data);
                new_node->set_next_node(nullptr);
                tail_node->set_next_node(new_node);
                size_++;
            }
        }

        inline void insert_at_head(T data) {
            const auto new_node = std::make_shared<Node<T>>();

            new_node->set_node_data(data);
            new_node->set_next_node(head_);
            head_ = new_node;

            size_++;
        }

        [[nodiscard]] inline bool delete_data_at_head() noexcept {
            if (is_empty()) {
                return false;
            }

            auto current_head = head_;
            // make the next head be equal to the next node.
            // which will make the current head lose its link
            // thus deleted
            head_ = head_->get_next_node();

            current_head.reset();

            size_--;
            return true;
        }

        [[nodiscard]] inline bool delete_data_at_tail() const noexcept {
            if (is_empty()) {
                return false;
            }

            // get the second to the last
            // element in the list
            auto element_before_tail = head_.get();
            while (element_before_tail->get_next_node()->get_next_node() != nullptr) {
                element_before_tail = element_before_tail->get_next_node().get();
            }

            // set the tail node to be nullptr
            // it means deleted
            element_before_tail->get_next_node().reset();
            element_before_tail->set_next_node(nullptr);

            return true;
        }

        [[nodiscard]] inline auto delete_data(T data) {
            if(is_empty()) {
                return false;
            }

            // node_to_find acts as the node on which -> next points to the
            // node we are looking for
            auto node_to_find = head_;
            if (node_to_find->get_node_data() == data) {
                return delete_data_at_head();
            }

            while (node_to_find->get_next_node() != nullptr) {
                if (node_to_find->get_next_node()->get_node_data() == data) {
                    auto current_node = node_to_find->get_next_node();
                    node_to_find->set_next_node(current_node->get_next_node());
                    current_node.reset();

                    size_--;
                    return true;
                }

                node_to_find = node_to_find->get_next_node();
            }

            return false;
        }

        [[nodiscard]] inline auto search(T data) {
            if (is_empty()) {
                return false;
            } 

            auto temp_node = head_;
            while (temp_node != nullptr) {
                if (data == temp_node->get_node_data()) {
                    return true;
                }
                temp_node = temp_node->get_next_node();
            }    

            return false;
        }

        [[nodiscard]] inline auto get_head() const {
            return head_;
        }

        [[nodiscard]] inline bool is_empty() const {
            return head_ == nullptr;
        };

        void print_list() const noexcept {
            if (is_empty()) {
                return;
            }

            auto temp = get_head();
            while (temp != nullptr) {
                std::cout << temp->get_node_data() << "\n";
                temp = temp->get_next_node();
            }
        }

        inline unsigned int size() {
            return size_;
        }

        inline void reverse() {
            std::shared_ptr<Node<T>> previous_node = nullptr; // Previous node for tracking will be used for swapping links
            auto current_node = get_head();
            std::shared_ptr<Node<T>> next_node = nullptr; // Points to the current node's next node.

            while (current_node != nullptr) {
                next_node = current_node->get_next_node();
                current_node->set_next_node(previous_node); // reverse side
                previous_node = current_node; // tracking the previous node, to be swapped linkage later
                current_node = next_node; // move current_node to next node
            }

            head_ = previous_node; // copy the previous node, which points to the new list head. Last node in the loop.
        }

        // TODO: Implement this
        inline auto reverse_sublist(int p, int q) {
            if (p == q) {
                // nothing to reverse.
                return head_;
            } 

            Node<T>* previous_node = nullptr;
            auto current_node = head_;

            return current_node;
        }

        inline void remove_duplicates() {
            // to attain O(n) we can use unordered_map or unordered_set
            // I think
            if (is_empty()) {
                return;
            }

            auto current_node = head_;
            std::shared_ptr<Node<T>> advanced_node = nullptr;
            std::shared_ptr<Node<T>> dup = nullptr;

            while (current_node != nullptr) {
                advanced_node = current_node;
                while (advanced_node->get_next_node() != nullptr) {
                    if (current_node->get_node_data() == advanced_node->get_next_node()->get_node_data()) {
                        dup = advanced_node->get_next_node();
                        advanced_node->set_next_node(current_node->get_next_node()->get_next_node());
                        size_--;

                        dup.reset();
                    } else {
                        advanced_node = advanced_node->get_next_node();
                    }
                }

                current_node = current_node->get_next_node();
            }
        }

        static auto union_list(std::unique_ptr<LinkedList> first, std::unique_ptr<LinkedList> second) {
            auto current_node = second->get_head();
            while (current_node != nullptr) {
                first->insert_at_tail(current_node->get_node_data());
                current_node = current_node->get_next_node();
            }
            
            first->remove_duplicates();

            return first;
        }

//        inline LinkedList* interserction(LinkedList* first, LinkedList* second) {
//            LinkedList* result_list = new LinkedList();
//
//            Node* first_head_node = first->get_head();
//            Node* second_head_node = second->get_head();
//
//            while (first_head_node != nullptr) {
//                while (second_head_node != nullptr) {
//                    if (first_head_node->get_node_data() == second_head_node->get_node_data()) {
//                        result_list->insert_at_head(first_head_node->get_node_data());
//                    }
//                    second_head_node = second_head_node->get_next_node();
//                }
//                first_head_node = first_head_node->get_next_node();
//                second_head_node = second->get_head();
//            }
//            result_list->remove_duplicates();
//
//            return result_list;
//        }
//
//        bool has_loop() {
//            if(is_empty()) {
//                return false;
//            }
//
//            Node* slow_ptr = head_; // iterates one by one
//            Node* fast_ptr = head_; // iterates twice
//
//            // while elements exist
//            while (slow_ptr && fast_ptr && fast_ptr->get_next_node() != nullptr) {
//                slow_ptr = slow_ptr->get_next_node(); // point to the next_ptr of current slow_node
//                fast_ptr = slow_ptr->get_next_node()->get_next_node(); // point to the next_ptr of the next_ptr of the current fast_node
//
//                if (slow_ptr == fast_ptr) {
//                    return true;
//                }
//            }
//            return false;
//        }
//
//        bool Delete(int value) {
//            bool deleted = false; //returns true if the node is deleted, false otherwise
//
//            if (is_empty()) { //check if the list is empty
//                return deleted; //deleted will be false
//            }
//
//            //if list is not empty, start traversing it from the head
//            Node * currentNode = head_; //currentNode to traverse the list
//            Node * previousNode = nullptr; //previousNode starts from null
//
//            if (currentNode->get_node_data() == value) { // deleting value of head
//                deleted = delete_data_at_head();
//                std::cout << value << " deleted!" << std::endl;
//                deleted = true; // true because value found and deleted
//                return deleted; //returns true if the node is deleted
//            }
//            previousNode = currentNode;
//            currentNode = currentNode->get_next_node(); // pointing current to current's nextElement
//            //Traversing/Searching for Node to Delete
//            while (currentNode != nullptr) {
//
//                //Node to delete is found
//                if (value == currentNode->get_node_data()) {
//                    // pointing previousNode's nextElement to currentNode's nextElement
//                    previousNode->set_next_node(currentNode->get_next_node());
//                    delete currentNode;
//                    currentNode = previousNode->get_next_node();
//                    deleted = true;
//                    break;
//                }
//                previousNode = currentNode;
//                currentNode = currentNode->get_next_node(); // pointing current to current's nextElement
//            }
//            //deleted is true only when value is found and delted
//            if (!deleted) {
//                std::cout << value << " does not exist!" << std::endl;
//            } else {
//                std::cout << value << " deleted!" << std::endl;
//            }
//            return deleted;
//        }
//
//        inline int get_mid() {
//            int mid_idx = size_ % 2 == 0 ? std::floor(size_ / 2) : std::floor(size_ / 2) + 1;
//
//            Node* current_node = head_;
//            if (current_node->get_next_node() == nullptr) {
//                // only 1 element in list
//                return current_node->get_node_data();
//            }
//
//            int counter = 0;
//            while (current_node != nullptr) {
//                if (counter == mid_idx - 1) {
//                    return current_node->get_node_data();
//                }
//                current_node = current_node->get_next_node();
//                counter++;
//            }
//
//            return 0;
//        }
//
//        inline int find_nth(int n) {
//            if (n > size() || is_empty()) {
//                return -1;
//            }
//            //O(n) - uses length
//            // Node* current_node = get_head();
//            // int counter = 0;
//            // while (current_node != nullptr && counter < size_ - n) {
//            //     current_node = current_node->get_next_node();
//            //     counter++;
//            // }
//
//            // if (current_node != nullptr) {
//            //     return current_node->get_node_data();
//            // }
//            Node* end_node = head_;
//            Node* nth_node = head_;
//
//            // Move the end_node to the n position
//            int counter = 0;
//            while (counter < n) {
//                // if it is out of bound then it will return an empty string.
//                if (end_node == nullptr) {
//                    return -1;
//                }
//                end_node = end_node->get_next_node();
//                counter++;
//            }
//
//            // at this point the "end_node" is at position "n"
//            // we will move the 2 pointers simultaneously, until the time end_node reaches nullptr.
//            while (end_node != nullptr) {
//                end_node = end_node->get_next_node();
//                nth_node = nth_node->get_next_node();
//            }
//
//            // check if nth_node is valid
//            if (nth_node != nullptr) {
//                return nth_node->get_node_data();
//            }
//
//            return -1;
//        }
        /** Another approach(to study)
        int LinkedList::findMid() {
    //list is empty
    if (isEmpty())
        return 0;

    //currentNode starts at the head
    Node * currentNode = head;

    if (currentNode->nextElement == nullptr) {
        //Only 1 element exist in array so return its value.
        return currentNode->data;
    }

    Node * midNode = currentNode; //midNode starts at head
    currentNode = currentNode->nextElement->nextElement; //currentNode moves two steps forward

    //Move midNode (Slower) one step at a time
    //Move currentNode (Faster) two steps at a time
    //When currentNode reaches at end, midNode will be at the middle of List
    while (currentNode != nullptr) {		// traversing from head to end

        midNode = midNode->nextElement;

        currentNode = currentNode->nextElement;		// pointing to current's next
        if (currentNode != nullptr)			
            currentNode = currentNode->nextElement;		// pointing to current's next

    }
    if(midNode != nullptr)		// pointing at middle of the list
        return midNode->data;
    return 0;
}
        **/

    private:
        std::shared_ptr<Node<T>> head_{}; // start of the list
        int size_ = 0;
};