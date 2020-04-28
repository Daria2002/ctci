#include "linked_list/MyLinkedList.hpp"

typedef MyLinkedListManager::Node node;
typedef MyLinkedListManager::LinkedList linked_list;

bool has_loop(node* head, node*& loop_node) {
    node* fast = head;
    node* slow = head;

    // move fast and slow to the same position
    while(fast != nullptr && fast -> next != nullptr) {
        fast = fast -> next -> next;
        slow = slow -> next;
        if(slow == fast) {
            break;
        }
    }
    // if fast and slow never collide there is no loop
    if(fast == nullptr || fast -> next == nullptr) {
        return fast;
    }

    fast = head;
    // move fast and slow for k steps till they collide at loop node
    while (fast != slow) {
        fast = fast -> next;
        slow = slow -> next;
    }
    loop_node = slow;
    return true;
}

/**
 * Given a linked list which might contain a loop, implement an
 * algorithm that returns the node at the beginning of the loop
 * (if one exists).
 * EXAMPLE:
 * Input: A -> B -> C -> D -> E -> C [the same C as earlier]
 * Output: C
 */
int main() {
    linked_list ll = MyLinkedListManager::get_linked_list();

    node* tail = MyLinkedListManager::get_tail(ll.head);
    std::cout << "Enter index of node you want to be loop node:\n";
    int index;
    std::cin >> index;
    node* loop_node_to_add = new node();
    if(MyLinkedListManager::get_node(ll, index, loop_node_to_add) == false) {
        std::cout << "Node index is greater than linked list length.\n";
        return 0; 
    }
    tail -> next = loop_node_to_add;

    node* loop_node = new node();
    if(has_loop(ll.head, loop_node)) {
        std::cout << "Loop node value = " << loop_node -> value << ".\n";
        return 0;
    }
    std::cout << "There is no loop.\n";
}