#include <iostream>
#include <memory>

class TreeNode {
    public:
        int _value;
        TreeNode() {}
        TreeNode(int value, std::shared_ptr<TreeNode> parent) : _value(value), _parent(parent) {}
        std::shared_ptr<TreeNode> _parent;
        std::shared_ptr<TreeNode> right;
        std::shared_ptr<TreeNode> left;
};  

std::shared_ptr<TreeNode> left_most_child(std::shared_ptr<TreeNode> node) {
    if(node == nullptr) {
        return nullptr;
    }
    while(node -> left != nullptr) {
        node = node -> left;
    }
    return node;
}

std::shared_ptr<TreeNode> get_successor(std::shared_ptr<TreeNode> node) {
    if(node == nullptr) {
        return nullptr;
    }
    if(node -> right == nullptr) {
        std::shared_ptr<TreeNode> parent = node -> _parent;
        std::shared_ptr<TreeNode> tmp = node;
        while(tmp != nullptr && parent != nullptr && parent -> left != tmp) {
            tmp = parent;
            parent = tmp -> _parent;
        }
        return parent;
    }
    return left_most_child(node -> right);
}

std::shared_ptr<TreeNode> get_BST() {
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(10, nullptr);
    root -> left = std::make_shared<TreeNode>(5, root);
    root -> right = std::make_shared<TreeNode>(20, root);
    root -> left -> left = std::make_shared<TreeNode>(4, root -> left);
    root -> right -> right = std::make_shared<TreeNode>(21, root -> right);
    root -> right -> left = std::make_shared<TreeNode>(15, root -> right);
    return root;
}

std::shared_ptr<TreeNode> get_node(int value, std::shared_ptr<TreeNode> root) {
    while (root -> _value != value) {
        if(root -> _value < value) {
            root = root -> right;
        } else {
            root = root -> left;
        }
    }
    return root;
}

// print bst using inorder traversal
void print_BST(std::shared_ptr<TreeNode> root) {
    if(root == nullptr) {
        return;
    }
    print_BST(root -> left);
    std::cout << root -> _value << '\n';
    print_BST(root -> right);
}

/**
 * Write an algorithm to find the "next" node (i.e., in-order successor) of a given node
 * in a binary search tree. You may assume that each node has a link to its parent.
 */ 
int main() {
    std::cout << "======================================================\n"
                 "Program to find the successor of a given node in a BST\n"
                 "======================================================\n";
    std::shared_ptr<TreeNode> root = get_BST();
    std::cout << "Created BST:\n";
    print_BST(root);
    std::cout << "Enter node value:\n";
    int value;
    std::cin >> value;
    std::shared_ptr<TreeNode> node = get_node(value, root);
    std::shared_ptr<TreeNode> successor = get_successor(node);
    if(successor == nullptr) {
        std::cout << "Successor of node " << value << " doesn't exist. " << 
        "Node " << value << " is the last node in BST.\n";
        return 0;
    }
    std::cout << "Successor of node " << value << " is " << successor -> _value << ".\n";
}