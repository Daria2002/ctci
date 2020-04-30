#include <iostream>
#include <vector>
#include <bits/stdc++.h> 

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
        TreeNode(int value) : _value(value) {}
};

TreeNode create_minimal_BST(const std::vector<int>& values, const int start, const int end) {
    if(values[start] == values[end]) {
        TreeNode node(values[start]);
        return node;
    }

    int middle_index = start + (end - start) / 2;

    TreeNode root(values[middle_index]);
    TreeNode left = create_minimal_BST(values, start, middle_index);
    TreeNode right = create_minimal_BST(values, middle_index, end);

    root.left = new TreeNode(left._value);
    root.right = new TreeNode(right._value);
    
    return root;
}

TreeNode create_minimal_BST(const std::vector<int>& values) {
    return create_minimal_BST(values, 0, values.size() - 1);
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
    create_minimal_BST(values);
    std::cout << "Minimal BST is created.\n";
}