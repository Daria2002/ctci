#include <iostream>
#include "MyLinkedList.hpp"

typedef MyLinkedListManager::LinkedList linked_list;
typedef MyLinkedListManager::Node Node;

void remove_node(Node*);

/**
 * Implement an algorithm to delete a node in the middle (i.e., any node
 * but the first and last node, not necessarily the exact middle) of a 
 * singly linked list, given only access to that node.
 * EXAMPLE
 * Input: the node c from the linked list a -> b -> c -> d -> e -> f
 * Result: nothing is returned, but the new linked list looks like a -> b -> d -> e -> f
 */
int main() {
    linked_list ll = MyLinkedListManager::get_linked_list();
    std::cout << "Enter the index of node to be removed" << std::endl;
    int index;
    std::cin >> index; 
    Node* node;
    if(MyLinkedListManager::get_node(ll, index, node) == false) {
        std::cout << "Index is greater than a size of linked list." << std::endl;
        return 0;
    }
    remove_node(node);
    MyLinkedListManager::print_linked_list(ll);
}

/**
 * This method is used in case if head node is not known.
 * Basically, it removes next node and changes node_to_remove value
 * and node_to_remove's next pointer.
 */
void remove_node(Node* node) {
    Node* next = node -> next;
    int new_value = next -> value;
    Node* new_next = next -> next;
    node -> value = new_value;
    node -> next = new_next;
}