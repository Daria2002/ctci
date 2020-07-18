#include <iostream>

class Node {
    public:
        Node() = default;
        Node(int v) : val(v) {}
        int val;
        Node* ptr1;
        Node* ptr2;
};

void initialize_node(Node** node) {
    *node = new Node(12);
    Node* n2 = new Node(15);
    Node* n3 = new Node(1);
    Node* n4 = new Node(7);
    Node* n5 = new Node(5);
    Node* n6 = new Node(19);
    (*node) -> ptr1 = n2;
    (*node) -> ptr2 = n3;
    n2 -> ptr1 = n4;
    n2 -> ptr2 = n5;
    n5 -> ptr1 = n6;
    n2 -> ptr2 = (*node);
}

/**
 * Write a method that takes a pointer to a Node structure as a parameter and returns a
 * complete copy of the passed in data structure. The Node data structure contains two 
 * pointers to other Nodes. 
 */
int main() {
    Node* root;
    initialize_node(&root);
}
