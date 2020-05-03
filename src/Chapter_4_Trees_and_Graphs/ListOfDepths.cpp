#include <iostream>
#include <vector>
#include <memory>
#include "linked_list/MyLinkedList.hpp"

typedef MyLinkedListManager::Node Node;
typedef MyLinkedListManager::LinkedList Linked_list;

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


std::shared_ptr<TreeNode> create_binary_tree(const std::vector<int>& values, const int start, const int end) {
    if(start > end) {
        return nullptr;
    }
    int middle_index = start + (end - start) / 2;
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(values[middle_index]);
    root -> left = create_binary_tree(values, start, middle_index - 1);
    root -> right = create_binary_tree(values, middle_index + 1, end);
    return root;
}

void get_linked_lists(std::shared_ptr<TreeNode> root, std::vector<Linked_list*>& linked_lists, int index) {
    if(root == nullptr) {
        return;
    }
    std::cout << "index = " << index << '\n';
    Linked_list ll;
    if(linked_lists.empty()) {
        linked_lists.push_back(&ll);
    }
    (*(linked_lists[index])).append_node(root -> _value);

    index++;
    get_linked_lists(root -> left, linked_lists, index);
    get_linked_lists(root -> right, linked_lists, index);

    return;
}

void get_linked_lists(const std::shared_ptr<TreeNode> root, std::vector<Linked_list*>& linked_lists) {
    int start = 0;
    get_linked_lists(root, linked_lists, start);
    return;
}

std::shared_ptr<TreeNode> create_binary_tree(const std::vector<int>& values) {
    std::shared_ptr<TreeNode> root(create_binary_tree(values, 0, values.size() - 1));
    return root;
}

/**
 * Given a binary tree, design an algorithm which creates a linked list of all the nodes 
 * at each depth (e.g., if you have a tree with depth D, you'll have D linked lists).
 */
int main() {
    std::cout << "===============================================================\n"
                 "Program for creating linked list for every level of binary tree\n"
                 "===============================================================\n";
    // std::vector<int> values = get_values();
    std::vector<int> values = {1, 5, 4, 7, 19, 10};
    std::shared_ptr<TreeNode> root(create_binary_tree(values));
    std::vector<Linked_list*> lists;
    get_linked_lists(root, lists);
    std::cout << "hello\n";
    return 0;
}