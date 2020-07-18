#include <iostream>
#include <unordered_map>

class Node {
    public:
        Node() = default;
        Node(int v) : val(v) {}
        int val;
        Node* ptr1;
        Node* ptr2;
};

// key - node address in the original structure,
// value - node address in the new structure
typedef std::unordered_map<Node*, Node*> NodeMap;

Node* copy_recursive(Node* cur, NodeMap& map) {
    if(cur == nullptr) return nullptr;
    NodeMap::iterator it = map.find(cur);
    // already copied
    if(it != map.end()) {
        return it -> second;
    }
    Node* node = new Node;
    map[cur] = node;
    node -> val = cur -> val;
    node -> ptr1 = copy_recursive(cur -> ptr1, map);
    node -> ptr2 = copy_recursive(cur -> ptr2, map);
    return node;
}

Node* copy_structure(Node* root) {
    NodeMap map;
    return copy_recursive(root, map);
}

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
    std::cout << "Root val = " << root -> val << '\n';
    std::cout << "Root ptr1 val = " << root -> ptr1 -> val << '\n';
    std::cout << "Root ptr2 val = " << root -> ptr2 -> val << '\n';
    Node* copy_root = copy_structure(root);
    std::cout << "Copy root val = " << copy_root -> val << '\n';
    std::cout << "Copy root ptr1 val = " << copy_root -> ptr1 -> val << '\n';
    std::cout << "Copy root ptr2 val = " << copy_root -> ptr2 -> val << '\n';
}
