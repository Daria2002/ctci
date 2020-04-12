#include <iostream>
#include "MyLinkedList.hpp" 

typedef MyLinkedListManager::LinkedList linked_list;
typedef MyLinkedListManager::Node node;

node* sum_linked_list(node*, node*);

/**
 * You have two numbers represented by a linked list, where each node 
 * contains a single digit. The digits are stored in reverse order, such
 * that the 1's digit is at the head of the list. Write a function that 
 * adds the two numbers and returns the sum as a linked list. (You are 
 * not allowed to "cheat" and just convert the linked list to an integer.)
 * EXAMPLE:
 * Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295.
 * Output: 2 -> 1 -> 9. That is, 912.
 * FOLLOWUP:
 * Suppose the digits are stored in forward order. Repeat the above problem.
 * EXAMPLE:
 * Input: (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295.
 * Output: 9 -> 1 -> 2. That is, 912.
 */
int main() {
    linked_list l1 = MyLinkedListManager::get_linked_list();
    linked_list l2 = MyLinkedListManager::get_linked_list();

    node* head_result = sum_linked_list(l1.head, l2.head);

    MyLinkedListManager::print_linked_list(head_result);
}


void sum_linked_list(node* head1, node* head2, node*& head_result, int residue) {
    int sum;
    if(head_result == nullptr) {
        head_result = new node();
    }
    if(head1 != nullptr && head2 != nullptr) {
        sum = head1 -> value + head2 -> value + residue;
        residue = sum/10;
        sum = sum % 10;
        head_result -> value = sum;
        sum_linked_list(head1 -> next, head2 -> next, head_result -> next, residue);
    } else if(head1 != nullptr) {
        sum = head1 -> value + residue;
        residue = sum/10;
        sum = sum % 10;
        head_result -> value = sum;
        sum_linked_list(head1 -> next, nullptr, head_result -> next, residue);
    } else if(head2 != nullptr) {
        sum = head2 -> value + residue;
        residue = sum/10;
        sum = sum % 10;
        head_result -> value = sum;
        sum_linked_list(nullptr, head2 -> next, head_result -> next, residue);
    } else {
        if(residue != 0) {
            head_result -> value = residue;
            head_result -> next = nullptr;
        } else {
            head_result = nullptr;
        }
    }
}

node* sum_linked_list(node* head1, node* head2) {
    node* head_result = new node();
    sum_linked_list(head1, head2, head_result, 0);
    return head_result;
}