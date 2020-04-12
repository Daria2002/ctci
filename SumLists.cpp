#include <iostream>
#include "MyLinkedList.hpp" 

typedef MyLinkedListManager::LinkedList linked_list;
typedef MyLinkedListManager::Node node;

node* sum_linked_list_reverse_order(node*, node*);
node* sum_linked_list_forward_order(node*, node*);
void insert_before(node*&, int, const int&);
void adapt_size(node*&, node*&);

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

    node* head_result_reverse_order = sum_linked_list_reverse_order(l1.head, l2.head);
    
    adapt_size(l1.head, l2.head);
    node* head_result_forward_order = sum_linked_list_forward_order(l1.head, l2.head);

    std::cout << "Approach: digits are in reverse order. ";
    MyLinkedListManager::print_linked_list(head_result_reverse_order);
    std::cout << "Approach: digits are in forward order. ";
    MyLinkedListManager::print_linked_list(head_result_forward_order);
}

void insert_before(node*& head, int number_of_insertions, const int& value_to_insert) {
    while (number_of_insertions > 0)
    {
        node* new_head = new node();
        new_head -> next = head;
        new_head -> value = value_to_insert;
        head = new_head;
        number_of_insertions--;
    }
}

void adapt_size(node*& head1, node*& head2) {
    int size1 = MyLinkedListManager::get_size(head1);
    int size2 = MyLinkedListManager::get_size(head2);
    if(size1 != size2) {
        size1 > size2 ? insert_before(head2, size1 - size2, 0) : insert_before(head1, size2 - size1, 0);
    }
}

void sum_linked_list_reverse_order(node* head1, node* head2, node*& head_result, int residue) {
    if(head1 == nullptr && head2 == nullptr && residue == 0) {
        return;
    }
    int sum = residue;
    head_result = new node();
    if(head1 != nullptr) {
        sum += head1 -> value;
    }
    if(head2 != nullptr) {
        sum += head2 -> value;
    }
    residue = sum/10;
    sum = sum % 10;
    head_result -> value = sum;
    if(head1 == nullptr || head2 == nullptr) {
        sum_linked_list_reverse_order(head1 == nullptr ? nullptr : head1 -> next,
                        head2 == nullptr ? nullptr : head2 -> next,
                        head_result -> next, residue);
        return;
    }
    sum_linked_list_reverse_order(head1 -> next, head2 -> next, head_result -> next, residue);
}

node* sum_linked_list_reverse_order(node* head1, node* head2) {
    node* head_result;
    sum_linked_list_reverse_order(head1, head2, head_result, 0);
    return head_result;
}

void sum_linked_list_forward_order(node* head1, node* head2, node*& head_result, int& residue) {
    if(head1 == nullptr && head2 == nullptr) {
        head_result = nullptr;
        residue = 0;
        return;
    }
    sum_linked_list_forward_order(head1 -> next, head2 -> next, head_result -> next, residue);
    int sum = head1 -> value + head2 -> value + residue;
    residue = sum / 10;
    sum = sum % 10;
    head_result -> value = sum;
    return;
}

node* sum_linked_list_forward_order(node* head1, node* head2) {
    node* head_result;
    int residue = 0;
    sum_linked_list_forward_order(head1, head2, head_result, residue);
    if(residue != 0) {
        node* new_head = new node();
        new_head -> value = residue;
        new_head -> next = head_result;
        head_result = new_head;
    }
    return head_result;
}