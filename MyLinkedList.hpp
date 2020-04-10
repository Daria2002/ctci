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

    LinkedList get_linked_list() {
        std::cout << "Enter elements for linked list. When you want to stop adding elements"
        " add non-number value" << std::endl;

        MyLinkedListManager::LinkedList ll;
        int value;
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
        return ll;
    }

    bool get_node(const LinkedList& ll, int index, Node*& node) {
        node = ll.head;
        while (index > 0) {
            node = node -> next;
            if(node == nullptr) {
                return false;
            }
            index--;
        }
        return true;
    }
}
    