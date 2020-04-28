#include <iostream>
#include "linked_list/MyLinkedList.hpp"

typedef MyLinkedListManager::LinkedList linked_list;
typedef MyLinkedListManager::Node node;

node* partition_mergining_two_lists(const linked_list&, const int&);
node* partition_using_head_and_tail_node(const linked_list&, const int&);

/**
 * Write code to partition a linked list around a value x, such that all nodes 
 * less than x come before all nodes greater than or equal to z. (IMPORTANT: The
 * partition element x can appear anywhere in the "right partition"; it does not
 * need to appear between the left and the right partitions. The additional
 * spacing the example below indicates the partition.) 
 * EXAMPLE: 
 * Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
 * Output: 3 -> 1 -> 2    ->     10 -> 5 -> 5 -> 8
 */
int main() {
    linked_list ll = MyLinkedListManager::get_linked_list();
    std::cout << "Enter a partition value:" << std::endl;
    int partition_value;
    std::cin >> partition_value;
    std::cout << "Enter 1 to partition a linked list around partition value using"
    " merging two lists method or 2 to partition using head and tail node.\n";
    int method;
    std::cin >> method;
    node* new_head = new node();
    switch (method)
    {
    case 1:
        new_head = partition_mergining_two_lists(ll, partition_value);
        break;
    case 2:
        new_head = partition_using_head_and_tail_node(ll, partition_value);
        break;
    default:
        std::cout << "Non of the proposed methods was choosen.\n";
        break;
    }
     
    MyLinkedListManager::print_linked_list(new_head);
}

node* partition_using_head_and_tail_node(const linked_list& ll, const int& partition_value) {
    node* head = ll.head;
    node* tail = ll.head;
    node* tmp = ll.head;
    while (tmp != nullptr) {
        node* next = tmp -> next;
        if(tmp -> value < partition_value) {
            tmp -> next = head;
            head = tmp;
        } else {
            tail -> next = tmp;
            tail = tmp;
        }
        tmp = next;
    }
    
    tail -> next = nullptr;
    return head;
}

node* partition_mergining_two_lists(const linked_list& ll, const int& partition_value) {
    node* smaller_list_head = nullptr;
    node* smaller_list_tail = nullptr;
    node* bigger_list_head = nullptr;
    node* bigger_list_tail = nullptr;

    node* tmp = ll.head;
    while (tmp != nullptr) {
        if(tmp -> value < partition_value) {
            if(smaller_list_head == nullptr) {
                smaller_list_head = tmp;
                smaller_list_tail = tmp;
            } else {
                smaller_list_tail -> next = tmp;
                smaller_list_tail = smaller_list_tail -> next;
            }
        } else {
            if(bigger_list_head == nullptr) {
                bigger_list_head = tmp;
                bigger_list_tail = tmp;
            } else {
                bigger_list_tail -> next = tmp;
                bigger_list_tail = bigger_list_tail -> next;
            }
        }
        tmp = tmp -> next;
    }

    if(smaller_list_head == nullptr) {
        return bigger_list_head;
    }

    // merge lists
    smaller_list_tail -> next = bigger_list_head;

    return smaller_list_head;
}