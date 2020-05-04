#include <iostream>
#include <memory>
#include <vector>
#include <limits>

class TreeNode {
    public:
        int _value;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        TreeNode() {}
        TreeNode(int value) : _value(value) {}
};

int height(std::shared_ptr<TreeNode>& root) {
    if(root == nullptr) {
        return -1;
    }
    int height_left = height(root -> left);
    int height_right = height(root -> right);

    if(height_right == std::numeric_limits<int>::min() || height_left == std::numeric_limits<int>::min()) {
        return std::numeric_limits<int>::min();
    }

    if(std::abs(height_right - height_left) > 1) {
        return std::numeric_limits<int>::min();
    }
    
    return std::max(height_left, height_right) + 1;
}

bool is_balanced(std::shared_ptr<TreeNode> root) {
    return (height(root) != std::numeric_limits<int>::min());
}

std::shared_ptr<TreeNode> get_balanced_tree() {
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(4);
    root -> left = std::make_shared<TreeNode>(5);
    root -> left -> right = std::make_shared<TreeNode>(10);
    root -> left -> left = std::make_shared<TreeNode>(19);
    root -> right = std::make_shared<TreeNode>(15);
    root -> right -> right = std::make_shared<TreeNode>(16);
    root -> right -> left = std::make_shared<TreeNode>(12);

    return root;
}

std::shared_ptr<TreeNode> get_unbalanced_tree() {
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(4);
    root -> left = std::make_shared<TreeNode>(5);
    root -> left -> right = std::make_shared<TreeNode>(10);
    root -> left -> left = std::make_shared<TreeNode>(19);
    root -> left -> left -> left = std::make_shared<TreeNode>(17);
    root -> right = std::make_shared<TreeNode>(15);

    return root;
}

/**
 * Implement a function to check if a binary tree is balanced. For the purposes of this question, 
 * a balanced tree is defined to be a tree such that the heights of the two subtrees of any node
 * never differ by more than one.
 */
int main() {
    std::cout << "=============================================\n"
                 "Program to check if a binary tree is balanced\n"
                 "=============================================\n";
    std::shared_ptr<TreeNode> root = get_unbalanced_tree();
    // std::shared_ptr<TreeNode> root = get_balanced_tree();
    std::cout << "Tree is " << (is_balanced(root) ? "" : "not ") << "balanced.\n";
}