#include <iostream>
#include "../include/linked list/MyLinkedList.hpp"
#include <unordered_set>

void remove_duplicates_using_hash_table(const MyLinkedListManager::LinkedList&);
void remove_duplicates_using_the_runnner_technique(const MyLinkedListManager::LinkedList&);

/**
 * Write a code to remove duplicates from an unsorted linked list
 * FOLLOW UP
 * How would you solve this problem if a temporary buffer is not allowed? 
 * 1st approach: use hash map, time complexity = O(N), space complexity = O(N)
 * 2nd approach: use The "runner" technique, time complexity = O(N^2), space complexity = O(1)
 */
int main() {
    MyLinkedListManager::LinkedList linked_list;
    int number_of_elements;
    std::cout << "How many elements you want to add to linked list?" << std::endl;
    std::cin >> number_of_elements;
    int value;
    while(number_of_elements > 0) {
        number_of_elements--;
        std::cin >> value;
        linked_list.append_node(value);
    }
    int method_chooser = 0;
    std::cout << "Choose method to remove duplicates. Enter 1 for method using hash_map "
    "or 2 for method using the \"runner\" technique." << std::endl;
    std::cin >> method_chooser;
    if(method_chooser == 1) {
        remove_duplicates_using_hash_table(linked_list);
    } else if(method_chooser == 2) {
        remove_duplicates_using_the_runnner_technique(linked_list);
    } else {
        std::cout << "You didn't choose none of the proposed methods, so linked list didn't change." << std::endl;
    }
    print_linked_list(linked_list);
}

void remove_duplicates_using_hash_table(const MyLinkedListManager::LinkedList& ll) {
    std::unordered_set<int> hash_table;
    MyLinkedListManager::Node* tmp = ll.head;
    MyLinkedListManager::Node* previous;
    while(tmp != nullptr) {
        // if value already occurred, remove it from linked list
        if(hash_table.find(tmp -> value) != hash_table.end()) {
            previous -> next = tmp -> next;
        } else { // if value has never occurred, add it in hash table
            hash_table.insert(tmp -> value);
        }
        previous = tmp;
        tmp = tmp -> next;
    }
}

void remove_duplicates_using_the_runnner_technique(const MyLinkedListManager::LinkedList& ll) {
    MyLinkedListManager::Node* current_node = ll.head;
    MyLinkedListManager::Node* checker;
    
    while(current_node != nullptr) {
        checker = current_node;
        while(checker -> next != nullptr) {
            if(checker -> next -> value == current_node -> value) {
                checker -> next = checker -> next -> next;
            } else {
                checker = checker -> next;
            }
        }
        current_node = current_node -> next;
    }
}