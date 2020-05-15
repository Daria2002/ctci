#include <iostream>
#include <memory>

class Node {
    public:
        Node() {}
        Node(int val) : value(val) {}
        Node(int val, int l, int r) : value(val), left(std::make_shared<Node>(l)), right(std::make_shared<Node>(r)) {}
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        int value;
};

using NodePtr = std::shared_ptr<Node>;

void create_bigger_tree(NodePtr& root) {
    root = std::make_shared<Node>(20, 25, 14);
    root -> left -> left = std::make_shared<Node>(17, 30, 70);
    root -> left -> right = std::make_shared<Node>(12, 40, 90);
    root -> right -> left = std::make_shared<Node>(11, 50, 80);
    root -> right -> right = std::make_shared<Node>(2, 60, 55);
}

void create_smaller_nonsubtree(NodePtr& root) {
    root = std::make_shared<Node>(11, 43, 3);
    root -> left -> left = std::make_shared<Node>(1);
    root -> left -> right = std::make_shared<Node>(2);
    root -> right -> left = std::make_shared<Node>(4);
    root -> right -> right = std::make_shared<Node>(5);
}

void create_smaller_subtree(NodePtr& root) {
    root = std::make_shared<Node>(17, 30, 70);
    root = std::make_shared<Node>(12, 40, 90);
}

bool is_subtree(const NodePtr& root1, const NodePtr& root2) {
    // return true if both trees empty or if subtree empty because empty tree is subtree of any tree
    if(root1 == nullptr && root2 == nullptr || root1 != nullptr && root2 == nullptr) {
        return true;
    }
    // if subtree is not empty and tree is empty return false
    if(root1 == nullptr) {
        return false;
    }
    // check left and right of the tree if current node in the tree is not same as the subtree root
    if(root1 -> value != root2 -> value) {
        return is_subtree(root1 -> left, root2) || is_subtree(root1 -> right, root2);
    }
    // root1 = root2
    return is_subtree(root1 -> left, root2 -> left) && is_subtree(root1 -> right, root2 -> right);
}

void create_preorder_traversal(const NodePtr& node, std::string& str) {
    if(node == nullptr) {
        str.push_back('X');
        return;
    }
    str.push_back(node -> value);
    str.push_back(' ');
    create_preorder_traversal(node -> left, str);
    create_preorder_traversal(node -> right, str);
}

bool is_subtree_preorder_traversal(const NodePtr& root1, const NodePtr& root2) {
    std::string preorder_traversal1, preorder_traversal2;
    create_preorder_traversal(root1, preorder_traversal1);
    create_preorder_traversal(root2, preorder_traversal2);
    return preorder_traversal1.find(preorder_traversal2) != std::string::npos;
}

/**
 * T1 and T2 are two very large binary trees, with T1 much bigger than T2. Create an
 * algorithm to determine if T2 is a subtree of T1. A tree T2 is a subtree if T1 if
 * there exists a node n in T1 such that the subtree of n is identical to T2. That is,
 * if you cut off the tree at node n, the two trees would be identical.
 */
int main() {
    NodePtr t1;
    NodePtr t2;
    create_bigger_tree(t1);
    // create_smaller_nonsubtree(t2);
    create_smaller_subtree(t2);
    std::cout << "Enter 1 to check if T2 is a subtree of T1 using recursive function or 2 to check "
                 "if T2 is a subtree of T1 using a preorder traversal.\n";
    int method;
    bool result;
    std::cin >> method;
    switch (method) {
    case 1:
        result = is_subtree(t1, t2);
        break;
    case 2:
        result = is_subtree_preorder_traversal(t1, t2);
        break;
    default:
        std::cout << "None of the proposed methods have not been choosen.\n";
        return 0;
    }
    std::cout << "T2 is " << (result ? "" : "not ") << "a subtree of T1.\n";
}
