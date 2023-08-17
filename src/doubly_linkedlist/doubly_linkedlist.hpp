#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

#include "node.hpp"

template <typename T>
class DoublyLinkedList final {
 public:
  [[nodiscard]] bool operator==(const DoublyLinkedList<T>& rhs) const noexcept {
    auto current_node = this->head_;
    auto current_node_rhs = rhs->get_head();

    if (this->size_ != rhs->size_) {
      return false;
    }

    while (current_node != nullptr && current_node_rhs != nullptr) {
      if (current_node->get_node_data() == current_node_rhs->get_node_data()) {
        current_node = current_node->get_next_node();
        current_node_rhs = current_node_rhs->get_next_node();
        continue;
      }

      return false;
    }

    return true;
  }

  using NodePtr = Node<T>*;

  void insert_at(T data, int n) noexcept {
    if (is_empty()) {
      insert_at_head(data);
    } else {
      auto current_node = head_;
      auto idx{0};
      while (idx < n && current_node->get_next_node() != nullptr) {
        current_node = current_node->get_next_node();
        ++idx;
      }

      auto new_node = std::make_unique<Node<T>>(data);
      new_node->set_next_node(current_node->get_next_node());
      current_node->set_next_node(new_node);
      ++size_;
    }
  }

  void insert_at_tail([[maybe_unused]] T data) noexcept {
    // traverse the list until it is a nullptr(tail)
    if (is_empty()) {
      insert_at_head(data);
    } else {
      auto current_node = head_;
      while (current_node->get_next_node() != nullptr) {
        current_node = current_node->get_next_node();
      }

      const auto new_node = std::make_shared<Node<T>>(data);
      new_node->set_prev_node(current_node);
      new_node->set_next_node(nullptr);
      current_node->set_next_node(new_node);
      ++size_;
    }
  }

  void insert_at_head(T data) {
    const auto new_node = std::make_shared<Node<T>>(data);
    new_node->set_next_node(head_);
    if (nullptr != head_.get()) {
      head_->set_prev_node(new_node);
    }

    head_ = new_node;
    size_++;
  }

  [[nodiscard]] bool delete_data_at_head() noexcept {
    if (is_empty()) {
      return false;
    }

    auto current_node = head_;
    head_ = current_node->get_next_node();
    current_node.reset();
    --size_;

    return true;
  }

  [[nodiscard]] bool delete_data_at_tail() const noexcept {
    if (is_empty()) {
      return false;
    }

    auto current_node = head_;
    while (current_node->get_next_node()->get_next_node() != nullptr) {
      current_node = current_node->get_next_node();
    }

    current_node->get_next_node().reset();
    current_node->set_next_node(nullptr);
    return true;
  }

  [[nodiscard]] bool delete_data(T data) noexcept {
    if (is_empty()) {
      return false;
    }

    auto current_node = head_;
    while (current_node->get_next_node() != nullptr) {
      if (current_node->get_node_data() == data) {
        if (const auto node_prev = current_node->get_prev_node().lock()) {
            node_prev->set_next_node(current_node->get_next_node());
        }
        if (current_node->get_next_node() != nullptr) {
          current_node->get_next_node()->set_prev_node(
              current_node->get_prev_node());
        }

        return true;
      }

      current_node = current_node->get_next_node();
    }

    return false;
  }

  [[nodiscard]] bool search(T data) const noexcept {
    if (is_empty()) {
      return false;
    }

    auto current_node = head_;
    while (current_node != nullptr) {
      if (data == current_node->get_node_data()) {
        return true;
      }
      current_node = current_node->get_next_node();
    }

    return false;
  }

  [[nodiscard]] Node<T>* get_head() const noexcept { return head_.get(); }

  [[nodiscard]] Node<T>* get_tail(Node<T>* current_node) const noexcept {
    if (current_node->get_next_node() != nullptr) {
      current_node = current_node->get_next_node();
      return get_tail(current_node);
    }

    return current_node;
  }

  [[nodiscard]] NodePtr get_nth(int n) noexcept {
    if (is_empty()) {
      return nullptr;
    }

    if (n < 0) {
      return nullptr;
    }

    // O(n) use reverse
    //    reverse();
    //
    //    int idx{0};
    //    auto current_node{head_};
    //    while (idx < n - 1 && current_node != nullptr) {
    //      current_node = current_node->get_next_node();
    //      ++idx;
    //    }

    // O(n) 2 pointers
    auto current_node{head_};
    int tail_ptr{static_cast<int>(size_) - 1};
    int head_ptr{0};

    while ((tail_ptr - head_ptr) != n - 1 && current_node != nullptr) {
      current_node = current_node->get_next_node();
      ++head_ptr;
    }

    return current_node;
  }

  [[nodiscard]] bool is_empty() const noexcept { return head_ == nullptr; };

  [[nodiscard]] size_t size() const noexcept { return size_; }

  [[maybe_unused]] void print_list() const noexcept {
    if (is_empty()) {
      return;
    }

    auto temp = get_head();
    while (temp != nullptr) {
      std::cout << temp->get_node_data() << "\n";
      temp = temp->get_next_node();
    }
  }

  void reverse() noexcept {
    if (is_empty()) {
      return;
    }

    auto current_node = head_;
    decltype(current_node) previous_node;
    decltype(current_node) next_node;

    while (current_node != nullptr) {
      next_node = current_node->get_next_node();
      current_node->set_next_node(previous_node);
      previous_node = current_node;
      current_node = next_node;
    }

    head_ = previous_node;
  }

  void insert_loop() noexcept {
    auto current_node = head_;
    while (current_node->get_next_node() != nullptr) {
      current_node = current_node->get_next_node();
    }

    current_node->set_next_node(head_);
  }

  [[nodiscard]] bool detect_loop() const noexcept {
    if (is_empty()) {
      return false;
    }

    auto slow = head_;
    auto fast = head_;

    while (slow != nullptr && fast != nullptr &&
           fast->get_next_node() != nullptr) {
      slow = slow->get_next_node();                   // one node at a time
      fast = fast->get_next_node()->get_next_node();  // 2 nodes at a time

      if (fast == slow) {
        return true;
      }
    }

    return false;
  }

  [[nodiscard]] NodePtr mid() const noexcept {
    if (is_empty()) {
      return nullptr;
    }

    const auto mid =
        (size_ % 2 == 0) ? std::floor(size_ / 2) : std::floor(size_ / 2) + 1;
    int idx{0};  // first node
    auto current_node{head_};

    while (idx < mid - 1 && current_node != nullptr) {
      current_node = current_node->get_next_node();
      ++idx;
    }

    return current_node;
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

  void remove_duplicates() noexcept {
    if (is_empty()) {
      return;
    }

    auto current_node{head_};
    while (current_node != nullptr) {
      const auto data{current_node->get_node_data()};

      auto compare_node{current_node->get_next_node()};
      while (compare_node != nullptr) {
        if (data == compare_node->get_node_data() &&
            compare_node->get_next_node() == nullptr) {
          assert(delete_data_at_tail());
          break;
        } else if (data == compare_node->get_node_data() &&
                   compare_node->get_next_node() != nullptr) {
          current_node->set_next_node(compare_node->get_next_node());
          compare_node->set_next_node(nullptr);
          break;
        } else {
          compare_node = compare_node->get_next_node();
        }
      }

      current_node = current_node->get_next_node();
    }
  }

  //  static auto union_list(std::unique_ptr<LinkedList> first,
  //                         std::unique_ptr<LinkedList> second) noexcept {
  //    if (first->is_empty() && second->is_empty()) {
  //      return std::make_unique<LinkedList>();
  //    }
  //
  //    if (second->is_empty()) {
  //      return first;
  //    }
  //
  //    if (first->is_empty()) {
  //      return second;
  //    }
  //
  //    auto tail_node{first->get_tail(first->get_head())};
  //    tail_node->set_next_node(second->get_head());
  //
  //    // remove possible duplicates
  //    first->remove_duplicates();
  //
  //    return first;
  //  }

  //        inline LinkedList* interserction(LinkedList* first, LinkedList*
  //        second) {
  //            LinkedList* result_list = new LinkedList();
  //
  //            Node* first_head_node = first->get_head();
  //            Node* second_head_node = second->get_head();
  //
  //            while (first_head_node != nullptr) {
  //                while (second_head_node != nullptr) {
  //                    if (first_head_node->get_node_data() ==
  //                    second_head_node->get_node_data()) {
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
  //            while (slow_ptr && fast_ptr && fast_ptr->get_next_node() !=
  //            nullptr) {
  //                slow_ptr = slow_ptr->get_next_node(); // point to the
  //                next_ptr of current slow_node fast_ptr =
  //                slow_ptr->get_next_node()->get_next_node(); // point to the
  //                next_ptr of the next_ptr of the current fast_node
  //
  //                if (slow_ptr == fast_ptr) {
  //                    return true;
  //                }
  //            }
  //            return false;
  //        }
  //
  //        bool Delete(int value) {
  //            bool deleted = false; //returns true if the node is deleted,
  //            false otherwise
  //
  //            if (is_empty()) { //check if the list is empty
  //                return deleted; //deleted will be false
  //            }
  //
  //            //if list is not empty, start traversing it from the head
  //            Node * currentNode = head_; //currentNode to traverse the list
  //            Node * previousNode = nullptr; //previousNode starts from null
  //
  //            if (currentNode->get_node_data() == value) { // deleting value
  //            of head
  //                deleted = delete_data_at_head();
  //                std::cout << value << " deleted!" << std::endl;
  //                deleted = true; // true because value found and deleted
  //                return deleted; //returns true if the node is deleted
  //            }
  //            previousNode = currentNode;
  //            currentNode = currentNode->get_next_node(); // pointing current
  //            to current's nextElement
  //            //Traversing/Searching for Node to Delete
  //            while (currentNode != nullptr) {
  //
  //                //Node to delete is found
  //                if (value == currentNode->get_node_data()) {
  //                    // pointing previousNode's nextElement to currentNode's
  //                    nextElement
  //                    previousNode->set_next_node(currentNode->get_next_node());
  //                    delete currentNode;
  //                    currentNode = previousNode->get_next_node();
  //                    deleted = true;
  //                    break;
  //                }
  //                previousNode = currentNode;
  //                currentNode = currentNode->get_next_node(); // pointing
  //                current to current's nextElement
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
  //            int mid_idx = size_ % 2 == 0 ? std::floor(size_ / 2) :
  //            std::floor(size_ / 2) + 1;
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
  //                // if it is out of bound then it will return an empty
  //                string. if (end_node == nullptr) {
  //                    return -1;
  //                }
  //                end_node = end_node->get_next_node();
  //                counter++;
  //            }
  //
  //            // at this point the "end_node" is at position "n"
  //            // we will move the 2 pointers simultaneously, until the time
  //            end_node reaches nullptr. while (end_node != nullptr) {
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
currentNode = currentNode->nextElement->nextElement; //currentNode moves two
steps forward

//Move midNode (Slower) one step at a time
//Move currentNode (Faster) two steps at a time
//When currentNode reaches at end, midNode will be at the middle of List
while (currentNode != nullptr) {		// traversing from head to end

  midNode = midNode->nextElement;

  currentNode = currentNode->nextElement;		// pointing to current's
next if (currentNode != nullptr) currentNode = currentNode->nextElement;
// pointing to current's next

}
if(midNode != nullptr)		// pointing at middle of the list
  return midNode->data;
return 0;
}
  **/

 private:
  std::shared_ptr<Node<T>> head_{nullptr};  // start of the list
  std::shared_ptr<Node<T>> end_{
      nullptr};  // end of the list TODO insert at tail O(1) tail
                 // updates everytime a new node is added
  size_t size_{0};
};