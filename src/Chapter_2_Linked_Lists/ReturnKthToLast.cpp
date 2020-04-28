#include <iostream>
#include "linked_list/MyLinkedList.hpp"
#include <unordered_map>

typedef MyLinkedListManager::Node Node;
typedef MyLinkedListManager::LinkedList linked_list;

bool get_kth_runner_technique(Node*, const int&, int&);
Node* get_kth_recursion(Node*, const int&, int&);
Node* get_kth_recursion(Node*, const int&);

/**
 * Implement an algorithm to find the kth to last element
 * of a singly linked list.
 * i.e. if k=0, last element is returned
 */
int main() {
    int k, method, value;
    linked_list ll = MyLinkedListManager::get_linked_list();
    std::cout << "Enter k (program will return kth node value to last element):" << std::endl;
    std::cin >> k;
    std::cout << "Enter 1 to use recursion approach or 2 for the \"runner\" technique:" << std::endl;
    std::cin >> method;
    if(method == 1) {   
        value = get_kth_recursion(ll.head, k) -> value;
    } else if(method == 2) {
        if(get_kth_runner_technique(ll.head, k, value) == false) {
            std::cout << "k value is greater than a size of linked list!" << std::endl;
            return 0;
        }
    } else {
        std::cout << "Non of the proposed methods was choosen." << std::endl;
        return 0;
    }
    std::cout << "K-th value to the last is " << value << "." << std::endl;
}

bool get_kth_runner_technique(Node* head, const int& k, int& value) {
    Node* slow = head;
    Node* fast = head;
    int counter = k;

    // fast pointer is k steps ahead from slow pointer
    while(counter > 0) {
        fast = fast -> next;
        if(fast == nullptr) {
            return false;
        }
        counter--;
    }

    while(fast->next != nullptr) {
        fast = fast -> next;
        slow = slow -> next;
    }

    value = slow -> value;
    return true;
}

Node* get_kth_recursion(Node* head, const int& k) {
    int i = 0;
    return get_kth_recursion(head, k, i);
}

Node* get_kth_recursion(Node* head, const int& k, int& i) {
    if(head == nullptr) {
        return nullptr;
    }

    Node* node = get_kth_recursion(head -> next, k, i);
    i++;
    if(i - 1 == k) {
        return head;
    } 
    return node;
}