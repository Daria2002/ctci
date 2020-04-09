#include <iostream>

namespace MyLinkedListManager {
    class Node {
        public:
            int value;
            Node* next;
    };  
    class LinkedList {
        public:
            Node* head;
            LinkedList() {
                head = nullptr;
            }
            void append_node(int n) {
                Node* new_node = new Node();
                new_node -> value = n;
                new_node -> next = nullptr;
                if(head == nullptr) {
                    head = new_node;
                    return;
                }
                Node* tmp = head;
                while(tmp -> next != nullptr) {
                    tmp = tmp -> next;
                }
                tmp -> next = new_node;
                return;
            }
    };

    void print_linked_list(LinkedList ll) {
        Node* tmp = ll.head;
        std::cout << "Linked list:" << std::endl;
        while(tmp != nullptr) {
            std::cout << tmp -> value << std::endl;
            tmp = tmp -> next;
        }
    }
}
    