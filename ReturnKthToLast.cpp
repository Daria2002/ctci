#include <iostream>
#include "MyLinkedList.hpp"

typedef MyLinkedListManager::Node Node;

bool get_kth_runner_technique(Node*, const int&, int&);
int get_kth_recursion(Node*, const int&, int&);

/**
 * Implement an algorithm to find the kth to last element
 * of a singly linked list.
 * i.e. if k=0, last element is returned
 */
int main() {
    std::cout << "Enter elements for linked list. When you want to stop adding elements"
    " add non-number value" << std::endl;

    MyLinkedListManager::LinkedList ll;
    int value, k, method;
    std::string str_value;
    while(true) {
        std::cin >> str_value;
        try {
            value = std::stoi(str_value);
            ll.append_node(value);
        } catch(const std::exception& e) {
            break;
        }
    }
    std::cout << "Enter k (program will return kth node value to last element):" << std::endl;
    std::cin >> k;
    std::cout << "Enter 1 to use recursion approach or 2 for the \"runner\" technique:" << std::endl;
    std::cin >> method;
    if(method == 1) {   
        value = 0;
    } else if(method == 2) {
        if(get_kth_runner_technique(ll.head, k, value) == false) {
            std::cout << "k value is greater than a size of linked list!" << std::endl;
            return 0;
        }
    } else {
        std::cout << "Non of the proposed methods was choosen." << std::endl;
        return 0;
    }
    std::cout << "K-th value to the last is " << value << std::endl;
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

int get_kth_recursion(Node* head, const int& k, int& i) {

}