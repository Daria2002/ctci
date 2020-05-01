#include <iostream>
#include <vector>
#include <algorithm>

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
        TreeNode* left;
        TreeNode* right;
        TreeNode() {}
        TreeNode(int value) : _value(value) {}
};

TreeNode* create_minimal_BST(const std::vector<int>& values, const int start, const int end) {
    if(start > end) {
        return nullptr;
    }
    int middle_index = start + (end - start) / 2;
    TreeNode* root = new TreeNode(values[middle_index]);
    root -> left = create_minimal_BST(values, start, middle_index - 1);
    root -> right = create_minimal_BST(values, middle_index + 1, end);
    return root;
}

int get_depth(TreeNode* root, int& depth) {
    if(root == nullptr) {
        return 0;
    }
    int tmp1 = get_depth(root -> left, depth);
    int tmp2 = get_depth(root -> right, depth);
    depth = ((tmp1 > tmp2) ? tmp1 : tmp2);
    depth++;
    return depth;
}

void print_BST(TreeNode* root) {

}

TreeNode* create_minimal_BST(const std::vector<int>& values) {
    TreeNode* root = create_minimal_BST(values, 0, values.size() - 1);
    int depth = 0;
    get_depth(root, depth);
    std::cout << "Minimal BST depth = " << depth << '\n';
    print_BST(root);
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
    // std::vector<int> values = get_values();
    std::vector<int> values = {1, 3, 4, 5, 6, 7, 8}; // example
    std::sort(values.begin(), values.end(), std::less<int>());
    TreeNode* root = create_minimal_BST(values);
}