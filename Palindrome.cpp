#include <iostream>
#include "MyLinkedList.hpp"
#include <vector>
#include <bits/stdc++.h> 

typedef MyLinkedListManager::Node node;
typedef MyLinkedListManager::LinkedList linked_list;

bool is_palindrome_reverse_and_compare(const linked_list&);
bool is_equal(node*, node*);
linked_list reverse(const linked_list&);

/**
 * Implement a function to check if a linked list is a palindrom.
 */
int main() {
    std::cout << "Checking if a linked list is a palindrome.\n";
    linked_list ll = MyLinkedListManager::get_linked_list();
    bool is_palindrome = is_palindrome_reverse_and_compare(ll);
    std::cout << "Linked list is " << (is_palindrome ? "" : "not ") << "palindrome.\n";
}

bool is_equal(node* head1, node* head2) {
    while(head1 != nullptr && head2 != nullptr) {
        if(head1 -> value != head2 -> value) {
            return false;
        }
        head1 = head1 -> next;
        head2 = head2 -> next;
    }
    return (head1 == nullptr && head2 == nullptr);
}

linked_list reverse(const linked_list& ll1) {
    linked_list ll2;
    std::stack<int> stack;
    node* tmp = ll1.head;
    while(tmp != nullptr) {
        stack.push(tmp -> value);
        tmp = tmp -> next;
    }
    while(!stack.empty()) {
        int value = stack.top();
        stack.pop();
        if(ll2.head == nullptr) {
            ll2.head = new node(); 
            ll2.head -> value = value;
            tmp = ll2.head;
        } else {
            tmp -> next = new node();
            tmp -> next -> value = value;
            tmp = tmp -> next;
        }
    }
    return ll2;
}

bool is_palindrome_reverse_and_compare(const linked_list& ll1) {
    linked_list ll2 = reverse(ll1);
    return is_equal(ll1.head, ll2.head);
}