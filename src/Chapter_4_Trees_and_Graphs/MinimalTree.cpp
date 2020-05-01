#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

std::vector<int> get_values() {
    std::vector<int> v;
    std::string value;
    std::cout << "Enter values (enter non-number value to stop):\n";
    try {
        while(true) {
            std::cin >> value;
            v.push_back(std::stoi(value));
        }
    } catch(std::exception e) {
        std::cout << "Values are saved.\n";
    }

    return v;
}

class TreeNode {
    public:
        int _value;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        TreeNode() {}
        TreeNode(int value) : _value(value) {}
};

std::shared_ptr<TreeNode> create_minimal_BST(const std::vector<int>& values, const int start, const int end) {
    if(start > end) {
        return nullptr;
    }
    int middle_index = start + (end - start) / 2;
    std::shared_ptr<TreeNode> root(new TreeNode(values[middle_index]));
    root -> left = create_minimal_BST(values, start, middle_index - 1);
    root -> right = create_minimal_BST(values, middle_index + 1, end);
    return root;
}

int get_depth(std::shared_ptr<TreeNode> root, int& depth) {
    if(root == nullptr) {
        return 0;
    }
    int tmp1 = get_depth(root -> left, depth);
    int tmp2 = get_depth(root -> right, depth);
    depth = ((tmp1 > tmp2) ? tmp1 : tmp2);
    depth++;
    return depth;
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

std::shared_ptr<TreeNode> create_minimal_BST(const std::vector<int>& values) {
    std::shared_ptr<TreeNode> root = create_minimal_BST(values, 0, values.size() - 1);
    int depth = 0;
    get_depth(root, depth);
    std::cout << "Minimal BST depth = " << depth << '\n';
    return root;
}

/**
 * Given a sorted (increasing order) array with unique integer elements, 
 * write an algorithm to create a binary search tree with minimal height.
 */
int main() {
    std::cout <<"=============================================================\n"
                "Program for creating a binary search tree with minimal height\n"
                "=============================================================\n";
    std::vector<int> values = get_values();
    std::sort(values.begin(), values.end(), std::less<int>());
    std::shared_ptr<TreeNode> root = create_minimal_BST(values);
    print_BST(root);
}