#include <iostream>
#include "linked_list/MyLinkedList.hpp"
#include <vector>
#include <stack>

typedef MyLinkedListManager::Node node;
typedef MyLinkedListManager::LinkedList linked_list;

class Result {
    public:
        Result(bool result, node* node) : _result(result), _node(node) {};
        bool _result;
        node* _node;
};

bool is_palindrome_the_runner_technique(const linked_list&);
bool is_palindrome_reverse_and_compare(const linked_list&);
bool is_palindrome_recursive(const linked_list&);
Result is_palindrome_recursive(node*, int);
bool is_equal(node*, node*);
linked_list reverse(const linked_list&);

/**
 * Implement a function to check if a linked list is a palindrom.
 */
int main() {
    std::cout << "Checking if a linked list is a palindrome.\n";
    linked_list ll = MyLinkedListManager::get_linked_list();
    bool is_palindrome = is_palindrome_reverse_and_compare(ll);
    int method;
    std::cout << "Choose method to check: 1-reverse and compare, "
    "2-the \"runner\" technique, 3-recursive function.\n";
    std::cin >> method;

    switch (method) {
    case 1:
        is_palindrome = is_palindrome_reverse_and_compare(ll);
        break;
    case 2:
        is_palindrome = is_palindrome_the_runner_technique(ll);
        break;
    case 3:
        is_palindrome = is_palindrome_recursive(ll);
        break;
    default:
        std::cout << "None of the methods has not been choosen.\n";
        return 0;
    }

    std::cout << "Linked list is " << (is_palindrome ? "" : "not ") << "a palindrome.\n";
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

bool is_palindrome_recursive(const linked_list& ll) {
    int length = MyLinkedListManager::get_size(ll.head);
    return is_palindrome_recursive(ll.head, length)._result;
}

Result is_palindrome_recursive(node* head, int length) {
    // even number of nodes (return middle node closer to end)
    if(length == 0) {
        return Result(true, head);
    }
    // odd number of nodes (skip middle node)
    if(length == 1) {
        return Result(true, head -> next);
    }
    
    Result result = is_palindrome_recursive(head -> next, length - 2);
    if(result._node -> value != head -> value) {
        result._result = false;
    }

    result._node = result._node -> next;
    return result;
}

bool is_palindrome_the_runner_technique(const linked_list& ll1) {
    node* fast = ll1.head;
    node* slow = ll1.head;
    std::stack<int> stack;
    
    while(fast != nullptr && fast -> next != nullptr) {
        stack.push(slow -> value);
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    // odd numbers of elements in linked list
    if(fast != nullptr) {
        slow = slow -> next;
    }

    while (!stack.empty()) {
        int value = stack.top();
        stack.pop();
        if(value != slow -> value) {
            return false;
        }
        slow = slow -> next;
    }
    return true;
}

bool is_palindrome_reverse_and_compare(const linked_list& ll1) {
    linked_list ll2 = reverse(ll1);
    return is_equal(ll1.head, ll2.head);
}