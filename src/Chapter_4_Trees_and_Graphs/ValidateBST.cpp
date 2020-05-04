#include <iostream>
#include <memory>
#include <climits>

class TreeNode {
    public:
        int _value;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        TreeNode() {}
        TreeNode(int value) : _value(value) {}
};

bool is_BST_range_validation(std::shared_ptr<TreeNode>& root, int min, int max) {
    if(root == nullptr) {
        return true;
    }
    if((min != NULL && root -> _value <= min) || (max != NULL && root -> _value > max)) {
        return false;
    }
    if(!is_BST_range_validation(root->left, min, root -> _value) || !is_BST_range_validation(root -> right, root -> _value, max)) {
        return false;
    }
    return true;
}

bool is_BST_in_order_traversal(std::shared_ptr<TreeNode>& root, int& last_visited) {
    if(root == nullptr) {
        return true;
    }

    if(!is_BST_in_order_traversal(root -> left, last_visited)) {
        return false;
    }

    if(root -> _value <= last_visited) {
        return false;
    }
    last_visited = root -> _value;

    if(!is_BST_in_order_traversal(root -> right, last_visited)) {
        return false;
    }

    return true;
}

std::shared_ptr<TreeNode> get_BST() {
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(10);
    root -> left = std::make_shared<TreeNode>(5);
    root -> right = std::make_shared<TreeNode>(20);
    root -> left -> left = std::make_shared<TreeNode>(4);
    root -> right -> right = std::make_shared<TreeNode>(21);
    root -> right -> left = std::make_shared<TreeNode>(15);
    return root;
}

std::shared_ptr<TreeNode> get_no_BST() {
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(10);
    root -> left = std::make_shared<TreeNode>(5);
    root -> right = std::make_shared<TreeNode>(20);
    root -> left -> left = std::make_shared<TreeNode>(4);
    root -> right -> right = std::make_shared<TreeNode>(21);
    root -> right -> left = std::make_shared<TreeNode>(9);
    return root;
}

/**
 * Implement a function to check if a binary tree is a binary search tree.
 */
int main() {
    std::cout << "=================================================\n"
                 "Program for validating if a binary tree is a BST.\n"
                 "=================================================\n";
    std::shared_ptr<TreeNode> root = get_BST();
    // std::shared_ptr<TreeNode> root = get_no_BST();

    int method;
    std::cout << "Enter 1 to use range validation or 2 to use in-order validation:\n";
    std::cin >> method;
    switch (method) {
    case 1:
        std::cout << "Tree is " << (is_BST_range_validation(root, NULL, NULL) ? "" : "not ") << "a binary search tree.\n";
        break;
    case 2: 
        int last_visited;
        std::cout << "Tree is " << (is_BST_in_order_traversal(root, last_visited) ? "" : "not ") << "a binary search tree.\n";
        break;
    default:
        std::cout << "None of the proposed methods have not been choosen\n";
        break;
    }
}