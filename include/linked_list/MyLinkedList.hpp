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
            ~LinkedList() {
                Node* current = head;
                Node* next;
                while(current != nullptr) {
                    next = current -> next;
                    delete current;
                    current = next;
                }
                head = nullptr;
            }
            void append_node(int n) {
                if(head == nullptr) {
                    head = new Node();
                    head -> value = n;
                    return;
                }
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
            void append_node(Node* n) {
                if(head == nullptr) {
                    head = n;
                    return;
                }
                Node* tmp = head;
                while(tmp -> next != nullptr) {
                    tmp = tmp -> next;
                }
                tmp -> next = n;
                return;
            }
    };

    Node* get_tail(Node* head) {
        if(head == nullptr) {
            return head;
        }
        while (head -> next != nullptr) {
            head = head -> next;
        }
        return head;
    }

    void print_linked_list(const LinkedList& ll) {
        Node* tmp = ll.head;
        std::cout << "Linked list:\n";
        while(tmp != nullptr) {
            std::cout << tmp -> value << std::endl;
            tmp = tmp -> next;
        }
    }

    void print_linked_list(const Node* head) {
        std::cout << "Linked list:\n";
        while(head != nullptr) {
            std::cout << head -> value << std::endl;
            head = head -> next;
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

    int get_size(Node* head) {
        int size = 0;
        while (head != nullptr)
        {
            size++;
            head = head -> next;
        }
        return size;
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
    