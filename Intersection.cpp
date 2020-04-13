#include <iostream>
#include "MyLinkedList.hpp"

typedef MyLinkedListManager::Node node;
typedef MyLinkedListManager::LinkedList linked_list;

node* create_intersection() {
    node* head = new node();
    head -> value = 5;
    head -> next = new node();
    node* intersection = head -> next;
    intersection -> value = 2;
    intersection -> next = new node();
    intersection = intersection -> next;
    intersection -> value = 3;
    intersection -> next = nullptr;
    return head;
}

node* get_tail(node* head) {
    if(head == nullptr) {
        return head;
    }
    while (head -> next != nullptr) {
        head = head -> next;
    }
    return head;
}

bool same_tail(node* head1, node* head2) {
    node* tail1 = get_tail(head1);
    node* tail2 = get_tail(head2);
    return tail1 == tail2;
}

node get_intersection_node(node* head1, node* head2) {
    int length1 = MyLinkedListManager::get_size(head1);
    int length2 = MyLinkedListManager::get_size(head2);
    int offset;
    if(length1 > length2) {
        offset = length1 - length2;
        while (offset > 0) {
            head1 = head1 -> next;
            offset--;
        }
    }
    if(length2 > length1) {
        offset = length2 - length1;
        while (offset > 0) {
            head2 = head2 -> next;
            offset--;
        }
    }
    while (head1 != head2) {
        head1 = head1 -> next;
        head2 = head2 -> next;
    }
    return *head1;
}

node get_intersection_node(linked_list ll1, linked_list ll2) {
    if(same_tail(ll1.head, ll2.head)) {
        node intersection = get_intersection_node(ll1.head, ll2.head);
        return intersection;
    }
    std::cout << "tu je\n";
    // return nullptr;
}

/**
 * Given two (singly) linked lists, determine if a two lists intersects. Return the
 * intersection node. Note that the intersection is defined based on reference, not value.
 * That is, if the kth node of the first linked list is the exact same node (by reference)
 * as the jth node of the second linked list, then they are intersecting.
 */
int main() {
    linked_list ll1 = MyLinkedListManager::get_linked_list();
    linked_list ll2 = MyLinkedListManager::get_linked_list();
    node* intersection = create_intersection();
    ll1.append_node(intersection);
    ll2.append_node(intersection);
    
    node calculated_intersection = get_intersection_node(ll1, ll2);
    std::cout << "calculated intersection is node with value " << calculated_intersection.value << '.\n'; 
}